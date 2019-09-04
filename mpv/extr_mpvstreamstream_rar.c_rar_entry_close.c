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
struct TYPE_3__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_1__ stream_t ;
typedef  int /*<<< orphan*/  rar_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  RarFileDelete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rar_entry_close(stream_t *s)
{
    rar_file_t *rar_file = s->priv;
    RarFileDelete(rar_file);
}