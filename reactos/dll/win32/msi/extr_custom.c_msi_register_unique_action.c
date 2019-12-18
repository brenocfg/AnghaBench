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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  size_t UINT ;
struct TYPE_3__ {size_t unique_actions_count; int /*<<< orphan*/ ** unique_actions; } ;
typedef  TYPE_1__ MSIPACKAGE ;

/* Variables and functions */
 size_t ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ ** msi_alloc (int) ; 
 int /*<<< orphan*/ ** msi_realloc (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/ * strdupW (int /*<<< orphan*/  const*) ; 

UINT msi_register_unique_action( MSIPACKAGE *package, const WCHAR *action )
{
    UINT count;
    WCHAR **newbuf = NULL;

    TRACE("Registering %s as unique action\n", debugstr_w(action));

    count = package->unique_actions_count;
    package->unique_actions_count++;
    if (count != 0) newbuf = msi_realloc( package->unique_actions,
                                          package->unique_actions_count * sizeof(WCHAR *) );
    else newbuf = msi_alloc( sizeof(WCHAR *) );

    newbuf[count] = strdupW( action );
    package->unique_actions = newbuf;
    return ERROR_SUCCESS;
}