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
struct gl_parser_attrib {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct gl_parser_attrib*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void gl_parser_attrib_init(struct gl_parser_attrib *attr)
{
	memset(attr, 0, sizeof(struct gl_parser_attrib));
}