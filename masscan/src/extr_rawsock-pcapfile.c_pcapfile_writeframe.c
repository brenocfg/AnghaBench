#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct PcapFile {scalar_t__ byte_order; char* filename; int /*<<< orphan*/ * fp; int /*<<< orphan*/  frame_number; } ;

/* Variables and functions */
 scalar_t__ CAPFILE_BIGENDIAN ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 unsigned int fwrite (void const*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

void pcapfile_writeframe(
    struct PcapFile *capfile,
    const void *buffer,
    unsigned buffer_size,
    unsigned original_length,
    unsigned time_sec,
    unsigned time_usec)
{
    unsigned char header[16];

    if (capfile == NULL || capfile->fp == NULL)
        return;

    /*
     * Write timestamp
     */
    if (capfile->byte_order == CAPFILE_BIGENDIAN) {
        header[ 0] = (unsigned char)(time_sec>>24);
        header[ 1] = (unsigned char)(time_sec>>16);
        header[ 2] = (unsigned char)(time_sec>> 8);
        header[ 3] = (unsigned char)(time_sec>> 0);

        header[ 4] = (unsigned char)(time_usec>>24);
        header[ 5] = (unsigned char)(time_usec>>16);
        header[ 6] = (unsigned char)(time_usec>> 8);
        header[ 7] = (unsigned char)(time_usec>> 0);

        header[ 8] = (unsigned char)(buffer_size>>24);
        header[ 9] = (unsigned char)(buffer_size>>16);
        header[10] = (unsigned char)(buffer_size>> 8);
        header[11] = (unsigned char)(buffer_size>> 0);

        header[12] = (unsigned char)(original_length>>24);
        header[13] = (unsigned char)(original_length>>16);
        header[14] = (unsigned char)(original_length>> 8);
        header[15] = (unsigned char)(original_length>> 0);

    } else {
        header[ 0] = (unsigned char)(time_sec>> 0);
        header[ 1] = (unsigned char)(time_sec>> 8);
        header[ 2] = (unsigned char)(time_sec>>16);
        header[ 3] = (unsigned char)(time_sec>>24);

        header[ 4] = (unsigned char)(time_usec>> 0);
        header[ 5] = (unsigned char)(time_usec>> 8);
        header[ 6] = (unsigned char)(time_usec>>16);
        header[ 7] = (unsigned char)(time_usec>>24);

        header[ 8] = (unsigned char)(buffer_size>> 0);
        header[ 9] = (unsigned char)(buffer_size>> 8);
        header[10] = (unsigned char)(buffer_size>>16);
        header[11] = (unsigned char)(buffer_size>>24);

        header[12] = (unsigned char)(original_length>> 0);
        header[13] = (unsigned char)(original_length>> 8);
        header[14] = (unsigned char)(original_length>>16);
        header[15] = (unsigned char)(original_length>>24);

    }

    if (fwrite(header, 1, 16, capfile->fp) != 16) {
        fprintf(stderr, "%s:%lld: could not write packet header\n",
            capfile->filename, capfile->frame_number);
        perror(capfile->filename);
        fclose(capfile->fp);
        capfile->fp = NULL;
    }

    if (fwrite(buffer, 1, buffer_size, capfile->fp) != buffer_size) {
        fprintf(stderr, "%s:%lld: could not write packet contents\n",
            capfile->filename, capfile->frame_number);
        perror(capfile->filename);
        fclose(capfile->fp);
        capfile->fp = NULL;
    }
}