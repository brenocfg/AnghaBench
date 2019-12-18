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
struct TYPE_4__ {scalar_t__ fd; } ;
struct TYPE_3__ {scalar_t__ fd; } ;
struct sendfile_cache_data {TYPE_2__ uncompressed; TYPE_1__ compressed; } ;
struct file_cache_entry {struct sendfile_cache_data sendfile_cache_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 

__attribute__((used)) static void sendfile_free(struct file_cache_entry *fce)
{
    struct sendfile_cache_data *sd = &fce->sendfile_cache_data;

    if (sd->compressed.fd >= 0)
        close(sd->compressed.fd);
    if (sd->uncompressed.fd >= 0)
        close(sd->uncompressed.fd);
}