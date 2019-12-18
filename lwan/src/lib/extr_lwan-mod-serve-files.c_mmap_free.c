#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  value; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; } ;
struct TYPE_5__ {int /*<<< orphan*/  len; int /*<<< orphan*/  value; } ;
struct mmap_cache_data {TYPE_4__ zstd; TYPE_3__ brotli; TYPE_2__ deflated; TYPE_1__ uncompressed; } ;
struct file_cache_entry {struct mmap_cache_data mmap_cache_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmap_free(struct file_cache_entry *fce)
{
    struct mmap_cache_data *md = &fce->mmap_cache_data;

    munmap(md->uncompressed.value, md->uncompressed.len);
    free(md->deflated.value);
#if defined(HAVE_BROTLI)
    free(md->brotli.value);
#endif
#if defined(HAVE_ZSTD)
    free(md->zstd.value);
#endif
}