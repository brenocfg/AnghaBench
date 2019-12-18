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

/* Variables and functions */
 int /*<<< orphan*/  ADD (char*,char*,int,int) ; 
 int /*<<< orphan*/  DEF_FIELD (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DEF_FIELD_ADDR (void*,int /*<<< orphan*/ ,int**) ; 
 int PCMCIA_DEV_ID_MATCH_CARD_ID ; 
 int PCMCIA_DEV_ID_MATCH_DEVICE_NO ; 
 int PCMCIA_DEV_ID_MATCH_FUNCTION ; 
 int PCMCIA_DEV_ID_MATCH_FUNC_ID ; 
 int PCMCIA_DEV_ID_MATCH_MANF_ID ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID1 ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID2 ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID3 ; 
 int PCMCIA_DEV_ID_MATCH_PROD_ID4 ; 
 int TO_NATIVE (int) ; 
 int /*<<< orphan*/  add_wildcard (char*) ; 
 int card_id ; 
 int device_no ; 
 int func_id ; 
 int function ; 
 int manf_id ; 
 int match_flags ; 
 int /*<<< orphan*/  pcmcia_device_id ; 
 int** prod_id_hash ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int do_pcmcia_entry(const char *filename,
			   void *symval, char *alias)
{
	unsigned int i;
	DEF_FIELD(symval, pcmcia_device_id, match_flags);
	DEF_FIELD(symval, pcmcia_device_id, manf_id);
	DEF_FIELD(symval, pcmcia_device_id, card_id);
	DEF_FIELD(symval, pcmcia_device_id, func_id);
	DEF_FIELD(symval, pcmcia_device_id, function);
	DEF_FIELD(symval, pcmcia_device_id, device_no);
	DEF_FIELD_ADDR(symval, pcmcia_device_id, prod_id_hash);

	for (i=0; i<4; i++) {
		(*prod_id_hash)[i] = TO_NATIVE((*prod_id_hash)[i]);
	}

	strcpy(alias, "pcmcia:");
	ADD(alias, "m", match_flags & PCMCIA_DEV_ID_MATCH_MANF_ID,
	    manf_id);
	ADD(alias, "c", match_flags & PCMCIA_DEV_ID_MATCH_CARD_ID,
	    card_id);
	ADD(alias, "f", match_flags & PCMCIA_DEV_ID_MATCH_FUNC_ID,
	    func_id);
	ADD(alias, "fn", match_flags & PCMCIA_DEV_ID_MATCH_FUNCTION,
	    function);
	ADD(alias, "pfn", match_flags & PCMCIA_DEV_ID_MATCH_DEVICE_NO,
	    device_no);
	ADD(alias, "pa", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID1, (*prod_id_hash)[0]);
	ADD(alias, "pb", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID2, (*prod_id_hash)[1]);
	ADD(alias, "pc", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID3, (*prod_id_hash)[2]);
	ADD(alias, "pd", match_flags & PCMCIA_DEV_ID_MATCH_PROD_ID4, (*prod_id_hash)[3]);

	add_wildcard(alias);
	return 1;
}