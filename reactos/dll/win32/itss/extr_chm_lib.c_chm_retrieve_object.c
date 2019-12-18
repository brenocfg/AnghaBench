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
struct chmUnitInfo {scalar_t__ length; scalar_t__ space; scalar_t__ start; } ;
struct chmFile {scalar_t__ data_offset; int /*<<< orphan*/  compression_enabled; } ;
typedef  scalar_t__ LONGUINT64 ;
typedef  scalar_t__ LONGINT64 ;
typedef  scalar_t__ Int64 ;

/* Variables and functions */
 scalar_t__ CHM_UNCOMPRESSED ; 
 scalar_t__ _chm_decompress_region (struct chmFile*,unsigned char*,scalar_t__,scalar_t__) ; 
 scalar_t__ _chm_fetch_bytes (struct chmFile*,unsigned char*,scalar_t__,scalar_t__) ; 

LONGINT64 chm_retrieve_object(struct chmFile *h,
                               struct chmUnitInfo *ui,
                               unsigned char *buf,
                               LONGUINT64 addr,
                               LONGINT64 len)
{
    /* must be valid file handle */
    if (h == NULL)
        return 0;

    /* starting address must be in correct range */
    if (addr >= ui->length)
        return 0;

    /* clip length */
    if (addr + len > ui->length)
        len = ui->length - addr;

    /* if the file is uncompressed, it's simple */
    if (ui->space == CHM_UNCOMPRESSED)
    {
        /* read data */
        return _chm_fetch_bytes(h,
                                buf,
                                h->data_offset + ui->start + addr,
                                len);
    }

    /* else if the file is compressed, it's a little trickier */
    else /* ui->space == CHM_COMPRESSED */
    {
        Int64 swath=0, total=0;

        /* if compression is not enabled for this file... */
        if (! h->compression_enabled)
            return total;

        do {

            /* swill another mouthful */
            swath = _chm_decompress_region(h, buf, ui->start + addr, len);

            /* if we didn't get any... */
            if (swath == 0)
                return total;

            /* update stats */
            total += swath;
            len -= swath;
            addr += swath;
            buf += swath;

        } while (len != 0);

        return total;
    }
}