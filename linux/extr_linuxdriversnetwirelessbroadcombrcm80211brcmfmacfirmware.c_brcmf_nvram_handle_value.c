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
typedef  char u8 ;
typedef  scalar_t__ u32 ;
struct nvram_parser {char* data; size_t pos; size_t entry; scalar_t__ nvram_len; char* nvram; int /*<<< orphan*/  column; } ;
typedef  enum nvram_parser_state { ____Placeholder_nvram_parser_state } nvram_parser_state ;

/* Variables and functions */
 scalar_t__ BRCMF_FW_MAX_NVRAM_SIZE ; 
 int END ; 
 int IDLE ; 
 int VALUE ; 
 int /*<<< orphan*/  is_nvram_char (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,scalar_t__) ; 

__attribute__((used)) static enum nvram_parser_state
brcmf_nvram_handle_value(struct nvram_parser *nvp)
{
	char c;
	char *skv;
	char *ekv;
	u32 cplen;

	c = nvp->data[nvp->pos];
	if (!is_nvram_char(c)) {
		/* key,value pair complete */
		ekv = (u8 *)&nvp->data[nvp->pos];
		skv = (u8 *)&nvp->data[nvp->entry];
		cplen = ekv - skv;
		if (nvp->nvram_len + cplen + 1 >= BRCMF_FW_MAX_NVRAM_SIZE)
			return END;
		/* copy to output buffer */
		memcpy(&nvp->nvram[nvp->nvram_len], skv, cplen);
		nvp->nvram_len += cplen;
		nvp->nvram[nvp->nvram_len] = '\0';
		nvp->nvram_len++;
		return IDLE;
	}
	nvp->pos++;
	nvp->column++;
	return VALUE;
}