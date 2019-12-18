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
typedef  scalar_t__ statement_type_t ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ STAT_FOR ; 
 scalar_t__ STAT_FORIN ; 
 scalar_t__ STAT_WHILE ; 

__attribute__((used)) static inline BOOL is_loop_statement(statement_type_t type)
{
    return type == STAT_FOR || type == STAT_FORIN || type == STAT_WHILE;
}