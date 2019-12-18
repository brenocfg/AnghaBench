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
typedef  int uint64_t ;
struct PcapFile {int bytes_read; int file_size; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */

unsigned pcapfile_percentdone(struct PcapFile *capfile, uint64_t *r_bytes_read)
{
    if (r_bytes_read)
        *r_bytes_read = capfile->bytes_read;

    if (capfile->fp == NULL)
        return 100;
    return (unsigned)(capfile->bytes_read*100/capfile->file_size);
}