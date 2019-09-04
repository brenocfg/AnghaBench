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
struct pl_parser {int dummy; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl_get_line0 (struct pl_parser*) ; 

__attribute__((used)) static bstr pl_get_line(struct pl_parser *p)
{
    return bstr0(pl_get_line0(p));
}