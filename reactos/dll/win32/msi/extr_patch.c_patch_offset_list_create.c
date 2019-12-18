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
struct patch_offset_list {int min; scalar_t__ max; scalar_t__ count; int /*<<< orphan*/  patches; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 struct patch_offset_list* msi_alloc (int) ; 

__attribute__((used)) static struct patch_offset_list *patch_offset_list_create( void )
{
    struct patch_offset_list *pos = msi_alloc( sizeof(struct patch_offset_list) );
    list_init( &pos->files );
    list_init( &pos->patches );
    pos->count = pos->max = 0;
    pos->min = 999999;
    return pos;
}