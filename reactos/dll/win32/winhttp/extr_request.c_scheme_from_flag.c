#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum auth_scheme { ____Placeholder_auth_scheme } auth_scheme ;
struct TYPE_2__ {scalar_t__ scheme; } ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int SCHEME_INVALID ; 
 TYPE_1__* auth_schemes ; 
 int num_auth_schemes ; 

__attribute__((used)) static enum auth_scheme scheme_from_flag( DWORD flag )
{
    int i;

    for (i = 0; i < num_auth_schemes; i++) if (flag == auth_schemes[i].scheme) return i;
    return SCHEME_INVALID;
}