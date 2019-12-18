#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* filter; int* mask; } ;
struct dmx_sct_filter_params {int flags; scalar_t__ timeout; TYPE_1__ filter; scalar_t__ pid; } ;
typedef  int /*<<< orphan*/  fparams ;
typedef  int /*<<< orphan*/  dvb_priv_t ;
typedef  int /*<<< orphan*/  demux_dev ;
typedef  int /*<<< orphan*/  buft ;

/* Variables and functions */
 int DMX_CHECK_CRC ; 
 int DMX_IMMEDIATE_START ; 
 int /*<<< orphan*/  DMX_SET_FILTER ; 
 scalar_t__ EOVERFLOW ; 
 int /*<<< orphan*/  MP_ERR (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct dmx_sct_filter_params*) ; 
 int /*<<< orphan*/  memset (struct dmx_sct_filter_params*,int,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

int dvb_get_pmt_pid(dvb_priv_t *priv, int devno, int service_id)
{
    /* We need special filters on the demux,
       so open one locally, and close also here. */
    char demux_dev[PATH_MAX];
    snprintf(demux_dev, sizeof(demux_dev), "/dev/dvb/adapter%d/demux0", devno);

    struct dmx_sct_filter_params fparams;

    memset(&fparams, 0x00, sizeof(fparams));
    fparams.pid = 0;
    fparams.filter.filter[0] = 0x00;
    fparams.filter.mask[0] = 0xff;
    fparams.timeout = 0;
    fparams.flags = DMX_IMMEDIATE_START | DMX_CHECK_CRC;

    int pat_fd;
    if ((pat_fd = open(demux_dev, O_RDWR)) < 0) {
        MP_ERR(priv, "Opening PAT DEMUX failed, error: %d", errno);
        return -1;
    }

    if (ioctl(pat_fd, DMX_SET_FILTER, &fparams) < 0) {
        MP_ERR(priv, "ioctl DMX_SET_FILTER failed, error: %d", errno);
        close(pat_fd);
        return -1;
    }

    int bytes_read;
    int section_length;
    unsigned char buft[4096];
    unsigned char *bufptr = buft;

    int pmt_pid = -1;

    bool pat_read = false;
    while (!pat_read) {
        if (((bytes_read =
                  read(pat_fd, bufptr,
                       sizeof(buft))) < 0) && errno == EOVERFLOW)
            bytes_read = read(pat_fd, bufptr, sizeof(buft));
        if (bytes_read < 0) {
            MP_ERR(priv, "PAT: read_sections: read error: %d", errno);
            close(pat_fd);
            return -1;
        }

        section_length = ((bufptr[1] & 0x0f) << 8) | bufptr[2];
        if (bytes_read != section_length + 3)
            continue;

        bufptr += 8;
        section_length -= 8;

        /* assumes one section contains the whole pat */
        pat_read = true;
        while (section_length > 0) {
            int this_service_id = (bufptr[0] << 8) | bufptr[1];
            if (this_service_id == service_id) {
                pmt_pid = ((bufptr[2] & 0x1f) << 8) | bufptr[3];
                section_length = 0;
            }
            bufptr += 4;
            section_length -= 4;
        }
    }
    close(pat_fd);

    return pmt_pid;
}