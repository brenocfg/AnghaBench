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
struct demux_cache {size_t file_pos; int /*<<< orphan*/  fd; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct demux_cache*,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  mp_strerror (int /*<<< orphan*/ ) ; 
 size_t read (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static bool read_raw(struct demux_cache *cache, void *ptr, size_t len)
{
    ssize_t res = read(cache->fd, ptr, len);

    if (res < 0) {
        MP_ERR(cache, "Failed to read cache file: %s\n", mp_strerror(errno));
        return false;
    }

    cache->file_pos += res;

    // Should never happen, unless the file was cut short, or someone succeeded
    // to rick us to write into a pipe or a socket.
    if (res != len) {
        MP_ERR(cache, "Could not read all data.\n");
        return false;
    }

    return true;
}