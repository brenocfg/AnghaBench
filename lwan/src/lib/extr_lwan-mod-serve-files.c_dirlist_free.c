#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct dir_list_cache_data {TYPE_2__ brotli; TYPE_1__ deflated; int /*<<< orphan*/  rendered; } ;
struct file_cache_entry {struct dir_list_cache_data dir_list_cache_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwan_strbuf_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dirlist_free(struct file_cache_entry *fce)
{
    struct dir_list_cache_data *dd = &fce->dir_list_cache_data;

    lwan_strbuf_free(&dd->rendered);
    free(dd->deflated.value);
#if defined(HAVE_BROTLI)
    free(dd->brotli.value);
#endif
}