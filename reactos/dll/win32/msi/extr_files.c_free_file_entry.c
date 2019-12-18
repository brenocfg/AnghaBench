#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* dest; struct TYPE_4__* source; } ;
typedef  TYPE_1__ FILE_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 

__attribute__((used)) static void free_file_entry(FILE_LIST *file)
{
    msi_free(file->source);
    msi_free(file->dest);
    msi_free(file);
}