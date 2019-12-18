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
struct ui_browser {struct map_symbol* priv; } ;
struct map_symbol {int /*<<< orphan*/  sym; } ;
struct annotation {int dummy; } ;

/* Variables and functions */
 struct annotation* symbol__annotation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct annotation *browser__annotation(struct ui_browser *browser)
{
	struct map_symbol *ms = browser->priv;
	return symbol__annotation(ms->sym);
}