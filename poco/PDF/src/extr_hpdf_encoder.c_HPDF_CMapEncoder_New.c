#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  sig_bytes; int /*<<< orphan*/  init_fn; int /*<<< orphan*/  free_fn; int /*<<< orphan*/  write_fn; int /*<<< orphan*/  to_unicode_fn; int /*<<< orphan*/  byte_type_fn; int /*<<< orphan*/  type; int /*<<< orphan*/  error; TYPE_1__* mmgr; scalar_t__ name; } ;
struct TYPE_8__ {int /*<<< orphan*/  error; } ;
typedef  TYPE_1__* HPDF_MMgr ;
typedef  int /*<<< orphan*/  HPDF_Encoder_Rec ;
typedef  int /*<<< orphan*/  HPDF_Encoder_Init_Func ;
typedef  TYPE_2__* HPDF_Encoder ;

/* Variables and functions */
 int /*<<< orphan*/  HPDF_CMapEncoder_ByteType ; 
 int /*<<< orphan*/  HPDF_CMapEncoder_Free ; 
 int /*<<< orphan*/  HPDF_CMapEncoder_ToUnicode ; 
 int /*<<< orphan*/  HPDF_CMapEncoder_Write ; 
 int /*<<< orphan*/  HPDF_ENCODER_SIG_BYTES ; 
 int /*<<< orphan*/  HPDF_ENCODER_TYPE_UNINITIALIZED ; 
 TYPE_2__* HPDF_GetMem (TYPE_1__*,int) ; 
 scalar_t__ HPDF_LIMIT_MAX_NAME_LEN ; 
 int /*<<< orphan*/  HPDF_MemSet (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_StrCpy (scalar_t__,char*,scalar_t__) ; 

HPDF_Encoder
HPDF_CMapEncoder_New  (HPDF_MMgr                mmgr,
                       char                    *name,
                       HPDF_Encoder_Init_Func   init_fn)
{
    HPDF_Encoder encoder;

    HPDF_PTRACE ((" HPDF_CMapEncoder_New\n"));

    if (mmgr == NULL)
        return NULL;

    encoder = HPDF_GetMem (mmgr, sizeof(HPDF_Encoder_Rec));
    if (!encoder)
        return NULL;

    HPDF_MemSet (encoder, 0, sizeof(HPDF_Encoder_Rec));

    HPDF_StrCpy (encoder->name, name, encoder->name + HPDF_LIMIT_MAX_NAME_LEN);
    encoder->mmgr = mmgr;
    encoder->error = mmgr->error;
    encoder->type = HPDF_ENCODER_TYPE_UNINITIALIZED;
    encoder->byte_type_fn = HPDF_CMapEncoder_ByteType;
    encoder->to_unicode_fn = HPDF_CMapEncoder_ToUnicode;
    encoder->write_fn = HPDF_CMapEncoder_Write;
    encoder->free_fn = HPDF_CMapEncoder_Free;
    encoder->init_fn = init_fn;
    encoder->sig_bytes = HPDF_ENCODER_SIG_BYTES;

    return encoder;
}