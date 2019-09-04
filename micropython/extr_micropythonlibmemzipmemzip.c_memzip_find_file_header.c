#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ signature; int /*<<< orphan*/  uncompressed_size; int /*<<< orphan*/  filename_len; int /*<<< orphan*/  extra_len; } ;
typedef  TYPE_1__ MEMZIP_FILE_HDR ;

/* Variables and functions */
 scalar_t__ MEMZIP_FILE_HEADER_SIGNATURE ; 
 scalar_t__ memzip_data ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int /*<<< orphan*/ ) ; 

const MEMZIP_FILE_HDR *memzip_find_file_header(const char *filename) {

    const MEMZIP_FILE_HDR *file_hdr = (const MEMZIP_FILE_HDR *)memzip_data;
    uint8_t *mem_data;

    /* Zip file filenames don't have a leading /, so we strip it off */

    if (*filename == '/') {
        filename++;
    }
    while (file_hdr->signature == MEMZIP_FILE_HEADER_SIGNATURE) {
        const char *file_hdr_filename = (const char *)&file_hdr[1];
        mem_data = (uint8_t *)file_hdr_filename;
        mem_data += file_hdr->filename_len;
        mem_data += file_hdr->extra_len;
        if (!strncmp(file_hdr_filename, filename, file_hdr->filename_len)) {
            /* We found a match */
            return file_hdr;
        }
        mem_data += file_hdr->uncompressed_size;
        file_hdr = (const MEMZIP_FILE_HDR *)mem_data;
    }
    return NULL;
}