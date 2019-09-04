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
struct mp_archive_volume {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int open_cb (struct archive*,void*) ; 
 int /*<<< orphan*/  volume_close (struct mp_archive_volume*) ; 

__attribute__((used)) static int switch_cb(struct archive *arch, void *oldpriv, void *newpriv)
{
    struct mp_archive_volume *oldvol = oldpriv;
    volume_close(oldvol);
    return open_cb(arch, newpriv);
}