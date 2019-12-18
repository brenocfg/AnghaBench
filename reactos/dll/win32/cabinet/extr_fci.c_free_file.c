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
struct file {int /*<<< orphan*/  entry; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* free ) (struct file*) ;} ;
typedef  TYPE_1__ FCI_Int ;

/* Variables and functions */
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct file*) ; 

__attribute__((used)) static void free_file( FCI_Int *fci, struct file *file )
{
    list_remove( &file->entry );
    fci->free( file );
}