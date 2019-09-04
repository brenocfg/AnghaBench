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
struct m_color {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; int /*<<< orphan*/  a; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 char* talloc_asprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *print_color(const m_option_t *opt, const void *val)
{
    const struct m_color *c = val;
    return talloc_asprintf(NULL, "#%02X%02X%02X%02X", c->a, c->r, c->g, c->b);
}