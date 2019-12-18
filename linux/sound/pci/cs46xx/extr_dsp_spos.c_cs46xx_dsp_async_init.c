#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_cs46xx {TYPE_1__* card; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_symbol_entry {int /*<<< orphan*/  address; } ;
struct dsp_spos_instance {int /*<<< orphan*/  the_null_scb; } ;
struct TYPE_6__ {int member_0; int member_1; } ;
struct TYPE_5__ {int member_0; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct dsp_spdifoscb {int member_3; int member_12; int member_14; int member_15; int /*<<< orphan*/  member_16; int /*<<< orphan*/  member_13; TYPE_3__ member_11; scalar_t__ member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; scalar_t__ member_2; TYPE_2__ member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_spdifiscb {int member_4; int member_5; int member_18; int member_19; int member_21; int member_22; int /*<<< orphan*/  member_23; int /*<<< orphan*/  member_20; scalar_t__ member_17; scalar_t__ member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; scalar_t__ member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_scb_descriptor {struct dsp_scb_descriptor* parent_scb_ptr; struct dsp_symbol_entry* task_entry; int /*<<< orphan*/  sub_list_ptr; struct dsp_scb_descriptor* next_scb_ptr; } ;
struct dsp_async_codec_input_scb {int member_3; int member_4; int member_5; int member_6; int member_8; int member_10; int member_17; int member_18; int member_20; int member_21; int member_22; int member_24; int member_25; int /*<<< orphan*/  member_26; int /*<<< orphan*/  member_23; int /*<<< orphan*/  member_19; scalar_t__ member_16; scalar_t__ member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; scalar_t__ member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_9; scalar_t__ member_7; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ASYNC_IP_OUTPUT_BUFFER1 ; 
 scalar_t__ AsyncCIOFIFOPointer ; 
 int /*<<< orphan*/  BA0_ASER_MASTER ; 
 int /*<<< orphan*/  DSP_SPOS_DC ; 
 int /*<<< orphan*/  DSP_SPOS_UU ; 
 int /*<<< orphan*/  DSP_SPOS_UUHI ; 
 int /*<<< orphan*/  DSP_SPOS_UULO ; 
 int /*<<< orphan*/  DSP_SPOS_UUUU ; 
 int EIO ; 
 int /*<<< orphan*/  FG_TASK_HEADER_ADDR ; 
 scalar_t__ HFG_TREE_SCB ; 
 int /*<<< orphan*/  NULL_SCB_ADDR ; 
 scalar_t__ RSCONFIG_MODULO_128 ; 
 scalar_t__ RSCONFIG_MODULO_256 ; 
 scalar_t__ RSCONFIG_MODULO_64 ; 
 scalar_t__ RSCONFIG_SAMPLE_16MONO ; 
 scalar_t__ RSCONFIG_SAMPLE_16STEREO ; 
 scalar_t__ SPDIFIFIFOPointer ; 
 int SPDIFI_IP_OUTPUT_BUFFER1 ; 
 scalar_t__ SPDIFI_SCB_INST ; 
 scalar_t__ SPDIFOFIFOPointer ; 
 int SPDIFO_IP_OUTPUT_BUFFER1 ; 
 scalar_t__ SPDIFO_SCB_INST ; 
 int /*<<< orphan*/  SYMBOL_CODE ; 
 struct dsp_scb_descriptor* cs46xx_dsp_create_scb (struct snd_cs46xx*,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 struct dsp_symbol_entry* cs46xx_dsp_lookup_symbol (struct snd_cs46xx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs46xx_dsp_proc_register_scb_desc (struct snd_cs46xx*,struct dsp_scb_descriptor*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_cs46xx_pokeBA0 (struct snd_cs46xx*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cs46xx_dsp_async_init (struct snd_cs46xx *chip,
				  struct dsp_scb_descriptor * fg_entry)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_symbol_entry * s16_async_codec_input_task;
	struct dsp_symbol_entry * spdifo_task;
	struct dsp_symbol_entry * spdifi_task;
	struct dsp_scb_descriptor * spdifi_scb_desc, * spdifo_scb_desc, * async_codec_scb_desc;

	s16_async_codec_input_task = cs46xx_dsp_lookup_symbol(chip, "S16_ASYNCCODECINPUTTASK", SYMBOL_CODE);
	if (s16_async_codec_input_task == NULL) {
		dev_err(chip->card->dev,
			"dsp_spos: symbol S16_ASYNCCODECINPUTTASK not found\n");
		return -EIO;
	}
	spdifo_task = cs46xx_dsp_lookup_symbol(chip, "SPDIFOTASK", SYMBOL_CODE);
	if (spdifo_task == NULL) {
		dev_err(chip->card->dev,
			"dsp_spos: symbol SPDIFOTASK not found\n");
		return -EIO;
	}

	spdifi_task = cs46xx_dsp_lookup_symbol(chip, "SPDIFITASK", SYMBOL_CODE);
	if (spdifi_task == NULL) {
		dev_err(chip->card->dev,
			"dsp_spos: symbol SPDIFITASK not found\n");
		return -EIO;
	}

	{
		/* 0xBC0 */
		struct dsp_spdifoscb spdifo_scb = {
			/* 0 */ DSP_SPOS_UUUU,
			{
				/* 1 */ 0xb0, 
				/* 2 */ 0, 
				/* 3 */ 0, 
				/* 4 */ 0, 
			},
			/* NOTE: the SPDIF output task read samples in mono
			   format, the AsynchFGTxSCB task writes to buffer
			   in stereo format
			*/
			/* 5 */ RSCONFIG_SAMPLE_16MONO + RSCONFIG_MODULO_256,
			/* 6 */ ( SPDIFO_IP_OUTPUT_BUFFER1 << 0x10 )  |  0xFFFC,
			/* 7 */ 0,0, 
			/* 8 */ 0, 
			/* 9 */ FG_TASK_HEADER_ADDR, NULL_SCB_ADDR, 
			/* A */ spdifo_task->address,
			SPDIFO_SCB_INST + SPDIFOFIFOPointer,
			{
				/* B */ 0x0040, /*DSP_SPOS_UUUU,*/
				/* C */ 0x20ff, /*DSP_SPOS_UUUU,*/
			},
			/* D */ 0x804c,0,							  /* SPDIFOFIFOPointer:SPDIFOStatRegAddr; */
			/* E */ 0x0108,0x0001,					  /* SPDIFOStMoFormat:SPDIFOFIFOBaseAddr; */
			/* F */ DSP_SPOS_UUUU	  			          /* SPDIFOFree; */
		};

		/* 0xBB0 */
		struct dsp_spdifiscb spdifi_scb = {
			/* 0 */ DSP_SPOS_UULO,DSP_SPOS_UUHI,
			/* 1 */ 0,
			/* 2 */ 0,
			/* 3 */ 1,4000,        /* SPDIFICountLimit SPDIFICount */ 
			/* 4 */ DSP_SPOS_UUUU, /* SPDIFIStatusData */
			/* 5 */ 0,DSP_SPOS_UUHI, /* StatusData, Free4 */
			/* 6 */ DSP_SPOS_UUUU,  /* Free3 */
			/* 7 */ DSP_SPOS_UU,DSP_SPOS_DC,  /* Free2 BitCount*/
			/* 8 */ DSP_SPOS_UUUU,	/* TempStatus */
			/* 9 */ SPDIFO_SCB_INST, NULL_SCB_ADDR,
			/* A */ spdifi_task->address,
			SPDIFI_SCB_INST + SPDIFIFIFOPointer,
			/* NOTE: The SPDIF input task write the sample in mono
			   format from the HW FIFO, the AsynchFGRxSCB task  reads 
			   them in stereo 
			*/
			/* B */ RSCONFIG_SAMPLE_16MONO + RSCONFIG_MODULO_128,
			/* C */ (SPDIFI_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC,
			/* D */ 0x8048,0,
			/* E */ 0x01f0,0x0001,
			/* F */ DSP_SPOS_UUUU /* SPDIN_STATUS monitor */
		};

		/* 0xBA0 */
		struct dsp_async_codec_input_scb async_codec_input_scb = {
			/* 0 */ DSP_SPOS_UUUU,
			/* 1 */ 0,
			/* 2 */ 0,
			/* 3 */ 1,4000,
			/* 4 */ 0x0118,0x0001,
			/* 5 */ RSCONFIG_SAMPLE_16MONO + RSCONFIG_MODULO_64,
			/* 6 */ (ASYNC_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC,
			/* 7 */ DSP_SPOS_UU,0x3,
			/* 8 */ DSP_SPOS_UUUU,
			/* 9 */ SPDIFI_SCB_INST,NULL_SCB_ADDR,
			/* A */ s16_async_codec_input_task->address,
			HFG_TREE_SCB + AsyncCIOFIFOPointer,
              
			/* B */ RSCONFIG_SAMPLE_16STEREO + RSCONFIG_MODULO_64,
			/* C */ (ASYNC_IP_OUTPUT_BUFFER1 << 0x10),  /*(ASYNC_IP_OUTPUT_BUFFER1 << 0x10) | 0xFFFC,*/
      
#ifdef UseASER1Input
			/* short AsyncCIFIFOPointer:AsyncCIStatRegAddr;	       
			   Init. 0000:8042: for ASER1
			   0000:8044: for ASER2 */
			/* D */ 0x8042,0,
      
			/* short AsyncCIStMoFormat:AsyncCIFIFOBaseAddr;
			   Init 1 stero:8050 ASER1
			   Init 0  mono:8070 ASER2
			   Init 1 Stereo : 0100 ASER1 (Set by script) */
			/* E */ 0x0100,0x0001,
      
#endif
      
#ifdef UseASER2Input
			/* short AsyncCIFIFOPointer:AsyncCIStatRegAddr;
			   Init. 0000:8042: for ASER1
			   0000:8044: for ASER2 */
			/* D */ 0x8044,0,
      
			/* short AsyncCIStMoFormat:AsyncCIFIFOBaseAddr;
			   Init 1 stero:8050 ASER1
			   Init 0  mono:8070 ASER2
			   Init 1 Stereo : 0100 ASER1 (Set by script) */
			/* E */ 0x0110,0x0001,
      
#endif
      
			/* short AsyncCIOutputBufModulo:AsyncCIFree;
			   AsyncCIOutputBufModulo: The modulo size for   
			   the output buffer of this task */
			/* F */ 0, /* DSP_SPOS_UUUU */
		};

		spdifo_scb_desc = cs46xx_dsp_create_scb(chip,"SPDIFOSCB",(u32 *)&spdifo_scb,SPDIFO_SCB_INST);

		if (snd_BUG_ON(!spdifo_scb_desc))
			return -EIO;
		spdifi_scb_desc = cs46xx_dsp_create_scb(chip,"SPDIFISCB",(u32 *)&spdifi_scb,SPDIFI_SCB_INST);
		if (snd_BUG_ON(!spdifi_scb_desc))
			return -EIO;
		async_codec_scb_desc = cs46xx_dsp_create_scb(chip,"AsynCodecInputSCB",(u32 *)&async_codec_input_scb, HFG_TREE_SCB);
		if (snd_BUG_ON(!async_codec_scb_desc))
			return -EIO;

		async_codec_scb_desc->parent_scb_ptr = NULL;
		async_codec_scb_desc->next_scb_ptr = spdifi_scb_desc;
		async_codec_scb_desc->sub_list_ptr = ins->the_null_scb;
		async_codec_scb_desc->task_entry = s16_async_codec_input_task;

		spdifi_scb_desc->parent_scb_ptr = async_codec_scb_desc;
		spdifi_scb_desc->next_scb_ptr = spdifo_scb_desc;
		spdifi_scb_desc->sub_list_ptr = ins->the_null_scb;
		spdifi_scb_desc->task_entry = spdifi_task;

		spdifo_scb_desc->parent_scb_ptr = spdifi_scb_desc;
		spdifo_scb_desc->next_scb_ptr = fg_entry;
		spdifo_scb_desc->sub_list_ptr = ins->the_null_scb;
		spdifo_scb_desc->task_entry = spdifo_task;

		/* this one is faked, as the parnet of SPDIFO task
		   is the FG task tree */
		fg_entry->parent_scb_ptr = spdifo_scb_desc;

		/* for proc fs */
		cs46xx_dsp_proc_register_scb_desc (chip,spdifo_scb_desc);
		cs46xx_dsp_proc_register_scb_desc (chip,spdifi_scb_desc);
		cs46xx_dsp_proc_register_scb_desc (chip,async_codec_scb_desc);

		/* Async MASTER ENABLE, affects both SPDIF input and output */
		snd_cs46xx_pokeBA0(chip, BA0_ASER_MASTER, 0x1 );
	}

	return 0;
}