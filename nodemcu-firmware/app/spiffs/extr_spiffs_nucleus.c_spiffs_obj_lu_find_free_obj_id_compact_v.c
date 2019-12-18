#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8_t ;
struct TYPE_8__ {scalar_t__ span_ix; int flags; } ;
struct TYPE_9__ {scalar_t__ name; TYPE_1__ p_hdr; } ;
typedef  TYPE_2__ spiffs_page_object_ix_header ;
typedef  scalar_t__ spiffs_obj_id ;
struct TYPE_10__ {scalar_t__ min_obj_id; scalar_t__ max_obj_id; scalar_t__ compaction; scalar_t__ conflicting_name; } ;
typedef  TYPE_3__ spiffs_free_obj_id_state ;
typedef  int /*<<< orphan*/  spiffs_block_ix ;
struct TYPE_11__ {scalar_t__ work; } ;
typedef  TYPE_4__ spiffs ;
typedef  scalar_t__ s32_t ;

/* Variables and functions */
 scalar_t__ SPIFFS_ERR_CONFLICTING_NAME ; 
 scalar_t__ SPIFFS_OBJ_ID_DELETED ; 
 scalar_t__ SPIFFS_OBJ_ID_FREE ; 
 scalar_t__ SPIFFS_OBJ_ID_IX_FLAG ; 
 int /*<<< orphan*/  SPIFFS_OBJ_LOOKUP_ENTRY_TO_PADDR (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SPIFFS_OK ; 
 int SPIFFS_OP_C_READ ; 
 int SPIFFS_OP_T_OBJ_LU2 ; 
 int SPIFFS_PH_FLAG_DELET ; 
 int SPIFFS_PH_FLAG_FINAL ; 
 int SPIFFS_PH_FLAG_INDEX ; 
 scalar_t__ SPIFFS_VIS_COUNTINUE ; 
 scalar_t__ _spiffs_rd (TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static s32_t spiffs_obj_lu_find_free_obj_id_compact_v(spiffs *fs, spiffs_obj_id id, spiffs_block_ix bix, int ix_entry,
    const void *user_const_p, void *user_var_p) {
  (void)user_var_p;
  if (id != SPIFFS_OBJ_ID_FREE && id != SPIFFS_OBJ_ID_DELETED && (id & SPIFFS_OBJ_ID_IX_FLAG)) {
    s32_t res;
    const spiffs_free_obj_id_state *state = (const spiffs_free_obj_id_state*)user_const_p;
    spiffs_page_object_ix_header objix_hdr;

    res = _spiffs_rd(fs, SPIFFS_OP_T_OBJ_LU2 | SPIFFS_OP_C_READ,
        0, SPIFFS_OBJ_LOOKUP_ENTRY_TO_PADDR(fs, bix, ix_entry), sizeof(spiffs_page_object_ix_header), (u8_t*)&objix_hdr);
    if (res == SPIFFS_OK && objix_hdr.p_hdr.span_ix == 0 &&
        ((objix_hdr.p_hdr.flags & (SPIFFS_PH_FLAG_INDEX | SPIFFS_PH_FLAG_FINAL | SPIFFS_PH_FLAG_DELET)) ==
            (SPIFFS_PH_FLAG_DELET))) {
      // ok object look up entry
      if (state->conflicting_name && strcmp((const char *)state->conflicting_name, (char *)objix_hdr.name) == 0) {
        return SPIFFS_ERR_CONFLICTING_NAME;
      }

      id &= ~SPIFFS_OBJ_ID_IX_FLAG;
      if (id >= state->min_obj_id && id <= state->max_obj_id) {
        u8_t *map = (u8_t *)fs->work;
        int ix = (id - state->min_obj_id) / state->compaction;
        //SPIFFS_DBG("free_obj_id: add ix "_SPIPRIi" for id "_SPIPRIid" min"_SPIPRIid" max"_SPIPRIid" comp:"_SPIPRIi"\n", ix, id, state->min_obj_id, state->max_obj_id, state->compaction);
        map[ix]++;
      }
    }
  }
  return SPIFFS_VIS_COUNTINUE;
}