#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned short type_offset; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ NDR_PARAM_OIF ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* get_ndr_types_params (unsigned int*) ; 

__attribute__((used)) static unsigned short get_tfs_offset( int param )
{
    unsigned int nb_params;
    const NDR_PARAM_OIF *params = get_ndr_types_params( &nb_params );

    assert( param < nb_params );
    return params[param].u.type_offset;
}