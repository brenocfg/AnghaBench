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
struct nvram_parser {char* data; size_t pos; size_t entry; int /*<<< orphan*/  column; int /*<<< orphan*/  line; } ;
typedef  enum nvram_parser_state { ____Placeholder_nvram_parser_state } nvram_parser_state ;

/* Variables and functions */
 int COMMENT ; 
 int IDLE ; 
 int /*<<< orphan*/  INFO ; 
 int KEY ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_nvram_char (char) ; 
 scalar_t__ is_whitespace (char) ; 

__attribute__((used)) static enum nvram_parser_state brcmf_nvram_handle_idle(struct nvram_parser *nvp)
{
	char c;

	c = nvp->data[nvp->pos];
	if (c == '\n')
		return COMMENT;
	if (is_whitespace(c) || c == '\0')
		goto proceed;
	if (c == '#')
		return COMMENT;
	if (is_nvram_char(c)) {
		nvp->entry = nvp->pos;
		return KEY;
	}
	brcmf_dbg(INFO, "warning: ln=%d:col=%d: ignoring invalid character\n",
		  nvp->line, nvp->column);
proceed:
	nvp->column++;
	nvp->pos++;
	return IDLE;
}