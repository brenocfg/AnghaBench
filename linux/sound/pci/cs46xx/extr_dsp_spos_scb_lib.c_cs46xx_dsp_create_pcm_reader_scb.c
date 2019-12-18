#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct snd_cs46xx {TYPE_4__* card; struct dsp_spos_instance* dsp_spos_instance; } ;
struct dsp_spos_instance {int /*<<< orphan*/ * null_algorithm; } ;
struct dsp_scb_descriptor {int dummy; } ;
struct TYPE_7__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_6__ {int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dsp_generic_scb {int member_6; int member_7; TYPE_3__ member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ DMA_RQ_C1_DEST_MOD32 ; 
 scalar_t__ DMA_RQ_C1_SOURCE_MOD1024 ; 
 scalar_t__ DMA_RQ_C1_SOURCE_ON_HOST ; 
 scalar_t__ DMA_RQ_C1_WRITEBACK_DEST_FLAG ; 
 scalar_t__ DMA_RQ_C1_WRITEBACK_SRC_FLAG ; 
 scalar_t__ DMA_RQ_C2_AC_NONE ; 
 scalar_t__ DMA_RQ_C2_SIGNAL_SOURCE_PINGPONG ; 
 int DMA_RQ_SD_SP_SAMPLE_ADDR ; 
 int /*<<< orphan*/  NULL_SCB_ADDR ; 
 int /*<<< orphan*/  RSCONFIG_DMA_ENABLE ; 
 int RSCONFIG_MAX_DMA_SIZE_SHIFT ; 
 int RSCONFIG_MODULO_32 ; 
 int RSCONFIG_SAMPLE_16STEREO ; 
 int RSCONFIG_STREAM_NUM_SHIFT ; 
 int /*<<< orphan*/  SYMBOL_CODE ; 
 struct dsp_scb_descriptor* _dsp_create_generic_scb (struct snd_cs46xx*,char*,int*,int,int /*<<< orphan*/ *,struct dsp_scb_descriptor*,int) ; 
 int /*<<< orphan*/ * cs46xx_dsp_lookup_symbol (struct snd_cs46xx*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct dsp_scb_descriptor * 
cs46xx_dsp_create_pcm_reader_scb(struct snd_cs46xx * chip, char * scb_name,
                                 u16 sample_buffer_addr, u32 dest,
                                 int virtual_channel, u32 playback_hw_addr,
                                 struct dsp_scb_descriptor * parent_scb,
                                 int scb_child_type)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * scb;
  
	struct dsp_generic_scb pcm_reader_scb = {
    
		/*
		  Play DMA Task xfers data from host buffer to SP buffer
		  init/runtime variables:
		  PlayAC: Play Audio Data Conversion - SCB loc: 2nd dword, mask: 0x0000F000L
		  DATA_FMT_16BIT_ST_LTLEND(0x00000000L)   from 16-bit stereo, little-endian
		  DATA_FMT_8_BIT_ST_SIGNED(0x00001000L)   from 8-bit stereo, signed
		  DATA_FMT_16BIT_MN_LTLEND(0x00002000L)   from 16-bit mono, little-endian
		  DATA_FMT_8_BIT_MN_SIGNED(0x00003000L)   from 8-bit mono, signed
		  DATA_FMT_16BIT_ST_BIGEND(0x00004000L)   from 16-bit stereo, big-endian
		  DATA_FMT_16BIT_MN_BIGEND(0x00006000L)   from 16-bit mono, big-endian
		  DATA_FMT_8_BIT_ST_UNSIGNED(0x00009000L) from 8-bit stereo, unsigned
		  DATA_FMT_8_BIT_MN_UNSIGNED(0x0000b000L) from 8-bit mono, unsigned
		  ? Other combinations possible from:
		  DMA_RQ_C2_AUDIO_CONVERT_MASK    0x0000F000L
		  DMA_RQ_C2_AC_NONE               0x00000000L
		  DMA_RQ_C2_AC_8_TO_16_BIT        0x00001000L
		  DMA_RQ_C2_AC_MONO_TO_STEREO     0x00002000L
		  DMA_RQ_C2_AC_ENDIAN_CONVERT     0x00004000L
		  DMA_RQ_C2_AC_SIGNED_CONVERT     0x00008000L
        
		  HostBuffAddr: Host Buffer Physical Byte Address - SCB loc:3rd dword, Mask: 0xFFFFFFFFL
		  aligned to dword boundary
		*/
		/* Basic (non scatter/gather) DMA requestor (4 ints) */
		{ DMA_RQ_C1_SOURCE_ON_HOST +        /* source buffer is on the host */
		  DMA_RQ_C1_SOURCE_MOD1024 +        /* source buffer is 1024 dwords (4096 bytes) */
		  DMA_RQ_C1_DEST_MOD32 +            /* dest buffer(PCMreaderBuf) is 32 dwords*/
		  DMA_RQ_C1_WRITEBACK_SRC_FLAG +    /* ?? */
		  DMA_RQ_C1_WRITEBACK_DEST_FLAG +   /* ?? */
		  15,                             /* DwordCount-1: picked 16 for DwordCount because Jim */
		  /*        Barnette said that is what we should use since */
		  /*        we are not running in optimized mode? */
		  DMA_RQ_C2_AC_NONE +
		  DMA_RQ_C2_SIGNAL_SOURCE_PINGPONG + /* set play interrupt (bit0) in HISR when source */
		  /*   buffer (on host) crosses half-way point */
		  virtual_channel,                   /* Play DMA channel arbitrarily set to 0 */
		  playback_hw_addr,                  /* HostBuffAddr (source) */
		  DMA_RQ_SD_SP_SAMPLE_ADDR +         /* destination buffer is in SP Sample Memory */
		  sample_buffer_addr                 /* SP Buffer Address (destination) */
		},
		/* Scatter/gather DMA requestor extension   (5 ints) */
		{
			0,
			0,
			0,
			0,
			0 
		},
		/* Sublist pointer & next stream control block (SCB) link. */
		NULL_SCB_ADDR,NULL_SCB_ADDR,
		/* Pointer to this tasks parameter block & stream function pointer */
		0,NULL_SCB_ADDR,
		/* rsConfig register for stream buffer (rsDMA reg. is loaded from basicReq.daw */
		/*   for incoming streams, or basicReq.saw, for outgoing streams) */
		RSCONFIG_DMA_ENABLE +                 /* enable DMA */
		(19 << RSCONFIG_MAX_DMA_SIZE_SHIFT) + /* MAX_DMA_SIZE picked to be 19 since SPUD  */
		/*  uses it for some reason */
		((dest >> 4) << RSCONFIG_STREAM_NUM_SHIFT) + /* stream number = SCBaddr/16 */
		RSCONFIG_SAMPLE_16STEREO +
		RSCONFIG_MODULO_32,             /* dest buffer(PCMreaderBuf) is 32 dwords (256 bytes) */
		/* Stream sample pointer & MAC-unit mode for this stream */
		(sample_buffer_addr << 0x10),
		/* Fractional increment per output sample in the input sample buffer */
		0, 
		{
			/* Standard stereo volume control
			   default muted */
			0xffff,0xffff,
			0xffff,0xffff
		}
	};

	if (ins->null_algorithm == NULL) {
		ins->null_algorithm =  cs46xx_dsp_lookup_symbol (chip,"NULLALGORITHM",
								 SYMBOL_CODE);
    
		if (ins->null_algorithm == NULL) {
			dev_err(chip->card->dev,
				"dsp_spos: symbol NULLALGORITHM not found\n");
			return NULL;
		}    
	}

	scb = _dsp_create_generic_scb(chip,scb_name,(u32 *)&pcm_reader_scb,
				      dest,ins->null_algorithm,parent_scb,
				      scb_child_type);
  
	return scb;
}