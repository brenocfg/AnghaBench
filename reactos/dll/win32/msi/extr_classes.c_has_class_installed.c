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
struct TYPE_3__ {scalar_t__ action; int /*<<< orphan*/  ProgID; } ;
typedef  int /*<<< orphan*/  MSIPROGID ;
typedef  TYPE_1__ MSICLASS ;
typedef  int BOOL ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ INSTALLSTATE_LOCAL ; 
 TYPE_1__* get_progid_class (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static BOOL has_class_installed( const MSIPROGID *progid )
{
    const MSICLASS *class = get_progid_class( progid );
    if (!class || !class->ProgID) return FALSE;
    return (class->action == INSTALLSTATE_LOCAL);
}