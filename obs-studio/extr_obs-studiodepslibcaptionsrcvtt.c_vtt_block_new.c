#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* cue_tail; TYPE_2__* cue_head; TYPE_2__* style_tail; TYPE_2__* style_head; TYPE_2__* region_tail; TYPE_2__* region_head; } ;
typedef  TYPE_1__ vtt_t ;
struct TYPE_8__ {int type; double timestamp; double duration; size_t text_size; struct TYPE_8__* next; int /*<<< orphan*/ * cue_id; int /*<<< orphan*/ * cue_settings; } ;
typedef  TYPE_2__ vtt_block_t ;
typedef  char utf8_char_t ;
typedef  enum VTT_BLOCK_TYPE { ____Placeholder_VTT_BLOCK_TYPE } VTT_BLOCK_TYPE ;

/* Variables and functions */
#define  VTT_CUE 131 
#define  VTT_NOTE 130 
#define  VTT_REGION 129 
#define  VTT_STYLE 128 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ vtt_block_data (TYPE_2__*) ; 

vtt_block_t* vtt_block_new(vtt_t* vtt, const utf8_char_t* data, size_t size, enum VTT_BLOCK_TYPE type)
{
    vtt_block_t* block = malloc(sizeof(vtt_block_t) + size + 1);
    block->next = NULL;
    block->type = type;
    block->timestamp = 0.0;
    block->duration = 0.0;
    block->cue_settings = NULL;
    block->cue_id = NULL;
    block->text_size = size;

    switch (type) {
    case VTT_REGION:
        if (vtt->region_head == NULL) {
            vtt->region_head = block;
        } else {
            vtt->region_tail->next = block;
        }
        vtt->region_tail = block;
        break;
    case VTT_STYLE:
        if (vtt->style_head == NULL) {
            vtt->style_head = block;
        } else {
            vtt->style_tail->next = block;
        }
        vtt->style_tail = block;
        break;
    case VTT_CUE:
        if (vtt->cue_head == NULL) {
            vtt->cue_head = block;
        } else {
            vtt->cue_tail->next = block;
        }
        vtt->cue_tail = block;
        break;
    case VTT_NOTE:
        break;
    }

    utf8_char_t* dest = (utf8_char_t*)vtt_block_data(block);
    if (data) {
        memcpy(dest, data, size);
    } else {
        memset(dest, 0, size);
    }

    dest[size] = '\0';
    return block;
}