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

/* Variables and functions */
 int parse_ini_thing (struct pl_parser*,char*,char*) ; 

__attribute__((used)) static int parse_pls(struct pl_parser *p)
{
    return parse_ini_thing(p, "[playlist]", "File");
}