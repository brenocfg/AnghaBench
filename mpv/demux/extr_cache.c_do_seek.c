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
typedef  scalar_t__ uint64_t ;
struct demux_cache {scalar_t__ file_pos; int /*<<< orphan*/  fd; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct demux_cache*,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool do_seek(struct demux_cache *cache, uint64_t pos)
{
    if (cache->file_pos == pos)
        return true;

    off_t res = lseek(cache->fd, pos, SEEK_SET);

    if (res == (off_t)-1) {
        MP_ERR(cache, "Failed to seek in cache file.\n");
        cache->file_pos = -1;
    } else {
        cache->file_pos = res;
    }

    return cache->file_pos >= 0;
}