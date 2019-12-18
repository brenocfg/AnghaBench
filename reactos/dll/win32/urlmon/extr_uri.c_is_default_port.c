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
typedef  scalar_t__ URL_SCHEME ;
struct TYPE_3__ {scalar_t__ scheme; scalar_t__ port; } ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* default_ports ; 

__attribute__((used)) static BOOL is_default_port(URL_SCHEME scheme, DWORD port) {
    DWORD i;

    for(i = 0; i < ARRAY_SIZE(default_ports); ++i) {
        if(default_ports[i].scheme == scheme && default_ports[i].port)
            return TRUE;
    }

    return FALSE;
}