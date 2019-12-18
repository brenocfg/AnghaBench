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
struct parser {scalar_t__ const* end; } ;
typedef  scalar_t__ CHAR ;

/* Variables and functions */
 scalar_t__ const CONTROL_Z ; 

__attribute__((used)) __inline static int is_eof(struct parser *parser, const CHAR *ptr)
{
    return (ptr >= parser->end || *ptr == CONTROL_Z);
}