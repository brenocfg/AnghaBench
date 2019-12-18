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
struct sectioncheck {int /*<<< orphan*/  symbol_white_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  data_sections ; 
 int /*<<< orphan*/  head_sections ; 
 int /*<<< orphan*/  init_data_sections ; 
 int /*<<< orphan*/  init_exit_sections ; 
 int /*<<< orphan*/  init_sections ; 
 int /*<<< orphan*/  linker_symbols ; 
 scalar_t__ match (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optim_symbols ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strstarts (char const*,char*) ; 
 int /*<<< orphan*/  text_sections ; 

__attribute__((used)) static int secref_whitelist(const struct sectioncheck *mismatch,
			    const char *fromsec, const char *fromsym,
			    const char *tosec, const char *tosym)
{
	/* Check for pattern 1 */
	if (match(tosec, init_data_sections) &&
	    match(fromsec, data_sections) &&
	    strstarts(fromsym, "__param"))
		return 0;

	/* Check for pattern 1a */
	if (strcmp(tosec, ".init.text") == 0 &&
	    match(fromsec, data_sections) &&
	    strstarts(fromsym, "__param_ops_"))
		return 0;

	/* Check for pattern 2 */
	if (match(tosec, init_exit_sections) &&
	    match(fromsec, data_sections) &&
	    match(fromsym, mismatch->symbol_white_list))
		return 0;

	/* Check for pattern 3 */
	if (match(fromsec, head_sections) &&
	    match(tosec, init_sections))
		return 0;

	/* Check for pattern 4 */
	if (match(tosym, linker_symbols))
		return 0;

	/* Check for pattern 5 */
	if (match(fromsec, text_sections) &&
	    match(tosec, init_sections) &&
	    match(fromsym, optim_symbols))
		return 0;

	/* Check for pattern 6 */
	if (strstarts(fromsym, ".L"))
		return 0;

	return 1;
}