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
typedef  scalar_t__ CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ jtC ; 
 scalar_t__ jtD ; 
 scalar_t__ jtL ; 

__attribute__((used)) static inline BOOL right_join_causing(CHAR joining_type)
{
    return (joining_type == jtL || joining_type == jtD || joining_type == jtC);
}