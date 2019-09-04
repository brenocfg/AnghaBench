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
struct nvram_parser {char* nvram; size_t nvram_len; scalar_t__ boardrev_found; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FW_DEFAULT_BOARDREV ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void brcmf_fw_add_defaults(struct nvram_parser *nvp)
{
	if (nvp->boardrev_found)
		return;

	memcpy(&nvp->nvram[nvp->nvram_len], &BRCMF_FW_DEFAULT_BOARDREV,
	       strlen(BRCMF_FW_DEFAULT_BOARDREV));
	nvp->nvram_len += strlen(BRCMF_FW_DEFAULT_BOARDREV);
	nvp->nvram[nvp->nvram_len] = '\0';
	nvp->nvram_len++;
}