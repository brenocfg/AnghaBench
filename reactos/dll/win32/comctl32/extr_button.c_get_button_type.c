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
typedef  int UINT ;
typedef  int LONG ;

/* Variables and functions */
 int BS_TYPEMASK ; 

__attribute__((used)) static inline UINT get_button_type( LONG window_style )
{
    return (window_style & BS_TYPEMASK);
}