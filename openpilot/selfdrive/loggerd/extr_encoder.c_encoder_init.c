#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  out_port ;
typedef  int /*<<< orphan*/  in_port ;
typedef  int /*<<< orphan*/  hecv_type ;
typedef  int /*<<< orphan*/  bitrate_type ;
typedef  int /*<<< orphan*/  avc ;
struct TYPE_22__ {char const* filename; int width; int height; int fps; int remuxing; int downscale; int segment; int num_in_bufs; int num_out_bufs; scalar_t__* in_buf_headers; int /*<<< orphan*/  free_in; scalar_t__* out_buf_headers; int /*<<< orphan*/  handle; int /*<<< orphan*/  state_cv; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  done_out; int /*<<< orphan*/ * codec_config; int /*<<< orphan*/  state; void* v_ptr2; void* u_ptr2; void* y_ptr2; int /*<<< orphan*/  lock; } ;
struct TYPE_16__ {int nFrameWidth; int nFrameHeight; int nSliceHeight; int xFramerate; int nBitrate; int /*<<< orphan*/  eColorFormat; int /*<<< orphan*/  eCompressionFormat; int /*<<< orphan*/  nStride; } ;
struct TYPE_17__ {TYPE_1__ video; } ;
struct TYPE_21__ {int nSize; int nBufferCountActual; int /*<<< orphan*/  nBufferSize; TYPE_2__ format; void* nPortIndex; int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {int nSize; int nPFrames; int /*<<< orphan*/  eLoopFilterMode; int /*<<< orphan*/  nAllowedPictureTypes; int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; scalar_t__ nBFrames; void* nPortIndex; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int nSize; int nTargetBitrate; int /*<<< orphan*/  eControlRate; void* nPortIndex; int /*<<< orphan*/  member_0; } ;
struct TYPE_18__ {int nSize; int /*<<< orphan*/  eLevel; int /*<<< orphan*/  eProfile; void* nPortIndex; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ OMX_VIDEO_PARAM_HEVCTYPE ;
typedef  TYPE_4__ OMX_VIDEO_PARAM_BITRATETYPE ;
typedef  TYPE_5__ OMX_VIDEO_PARAM_AVCTYPE ;
typedef  void* OMX_U32 ;
typedef  int /*<<< orphan*/  OMX_STRING ;
typedef  TYPE_5__* OMX_PTR ;
typedef  TYPE_7__ OMX_PARAM_PORTDEFINITIONTYPE ;
typedef  int /*<<< orphan*/  OMX_INDEXTYPE ;
typedef  int /*<<< orphan*/  OMX_BUFFERHEADERTYPE ;
typedef  TYPE_8__ EncoderState ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_FMT_NV12 ; 
 int OMX_AllocateBuffer (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMX_COLOR_FormatUnused ; 
 int /*<<< orphan*/  OMX_CommandStateSet ; 
 int OMX_ErrorNone ; 
 int OMX_FillThisBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int OMX_GetHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int OMX_GetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  OMX_IndexParamPortDefinition ; 
 int /*<<< orphan*/  OMX_IndexParamVideoAvc ; 
 int /*<<< orphan*/  OMX_IndexParamVideoBitrate ; 
 scalar_t__ OMX_IndexParamVideoHevc ; 
 int OMX_SendCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int OMX_SetParameter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  OMX_StateExecuting ; 
 int /*<<< orphan*/  OMX_StateIdle ; 
 int /*<<< orphan*/  OMX_StateLoaded ; 
 int /*<<< orphan*/  OMX_VIDEO_AVCLevel31 ; 
 int /*<<< orphan*/  OMX_VIDEO_AVCLoopFilterEnable ; 
 int /*<<< orphan*/  OMX_VIDEO_AVCProfileBaseline ; 
 int /*<<< orphan*/  OMX_VIDEO_CodingAVC ; 
 int /*<<< orphan*/  OMX_VIDEO_CodingHEVC ; 
 int /*<<< orphan*/  OMX_VIDEO_CodingUnused ; 
 int /*<<< orphan*/  OMX_VIDEO_HEVCHighTierLevel5 ; 
 int /*<<< orphan*/  OMX_VIDEO_HEVCProfileMain ; 
 int /*<<< orphan*/  OMX_VIDEO_PictureTypeB ; 
 int /*<<< orphan*/  OMX_Video_ControlRateVariable ; 
 scalar_t__ PORT_INDEX_IN ; 
 scalar_t__ PORT_INDEX_OUT ; 
 int /*<<< orphan*/  QOMX_COLOR_FORMATYUV420PackedSemiPlanar32m ; 
 int /*<<< orphan*/  VENUS_BUFFER_SIZE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  VENUS_Y_STRIDE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,int) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init_reentrant (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omx_callbacks ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_push (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  wait_for_state (TYPE_8__*,int /*<<< orphan*/ ) ; 

void encoder_init(EncoderState *s, const char* filename, int width, int height, int fps, int bitrate, bool h265, bool downscale) {
  int err;

  memset(s, 0, sizeof(*s));
  s->filename = filename;
  s->width = width;
  s->height = height;
  s->fps = fps;
  mutex_init_reentrant(&s->lock);

  if (!h265) {
    s->remuxing = true;
  }

  if (downscale) {
    s->downscale = true;
    s->y_ptr2 = malloc(s->width*s->height);
    s->u_ptr2 = malloc(s->width*s->height/4);
    s->v_ptr2 = malloc(s->width*s->height/4);
  }

  s->segment = -1;

  s->state = OMX_StateLoaded;

  s->codec_config = NULL;

  queue_init(&s->free_in);
  queue_init(&s->done_out);

  pthread_mutex_init(&s->state_lock, NULL);
  pthread_cond_init(&s->state_cv, NULL);

  if (h265) {
    err = OMX_GetHandle(&s->handle, (OMX_STRING)"OMX.qcom.video.encoder.hevc",
                        s, &omx_callbacks);
  } else {
    err = OMX_GetHandle(&s->handle, (OMX_STRING)"OMX.qcom.video.encoder.avc",
                        s, &omx_callbacks);
  }
  assert(err == OMX_ErrorNone);
  // printf("handle: %p\n", s->handle);

  // setup input port

  OMX_PARAM_PORTDEFINITIONTYPE in_port = {0};
  in_port.nSize = sizeof(in_port);
  in_port.nPortIndex = (OMX_U32) PORT_INDEX_IN;
  err = OMX_GetParameter(s->handle, OMX_IndexParamPortDefinition,
                         (OMX_PTR) &in_port);
  assert(err == OMX_ErrorNone);

  in_port.format.video.nFrameWidth = s->width;
  in_port.format.video.nFrameHeight = s->height;
  in_port.format.video.nStride = VENUS_Y_STRIDE(COLOR_FMT_NV12, s->width);
  in_port.format.video.nSliceHeight = s->height;
  // in_port.nBufferSize = (s->width * s->height * 3) / 2;
  in_port.nBufferSize = VENUS_BUFFER_SIZE(COLOR_FMT_NV12, s->width, s->height);
  in_port.format.video.xFramerate = (s->fps * 65536);
  in_port.format.video.eCompressionFormat = OMX_VIDEO_CodingUnused;
  // in_port.format.video.eColorFormat = OMX_COLOR_FormatYUV420SemiPlanar;
  in_port.format.video.eColorFormat = QOMX_COLOR_FORMATYUV420PackedSemiPlanar32m;

  err = OMX_SetParameter(s->handle, OMX_IndexParamPortDefinition,
                         (OMX_PTR) &in_port);
  assert(err == OMX_ErrorNone);


  err = OMX_GetParameter(s->handle, OMX_IndexParamPortDefinition,
                         (OMX_PTR) &in_port);
  assert(err == OMX_ErrorNone);
  s->num_in_bufs = in_port.nBufferCountActual;

  // printf("in width: %d, stride: %d\n",
  //   in_port.format.video.nFrameWidth, in_port.format.video.nStride);

  // setup output port

  OMX_PARAM_PORTDEFINITIONTYPE out_port = {0};
  out_port.nSize = sizeof(out_port);
  out_port.nPortIndex = (OMX_U32) PORT_INDEX_OUT;
  err = OMX_GetParameter(s->handle, OMX_IndexParamPortDefinition,
                         (OMX_PTR)&out_port);
  assert(err == OMX_ErrorNone);
  out_port.format.video.nFrameWidth = s->width;
  out_port.format.video.nFrameHeight = s->height;
  out_port.format.video.xFramerate = 0;
  out_port.format.video.nBitrate = bitrate;
  if (h265) {
    out_port.format.video.eCompressionFormat = OMX_VIDEO_CodingHEVC;
  } else {
    out_port.format.video.eCompressionFormat = OMX_VIDEO_CodingAVC;
  }
  out_port.format.video.eColorFormat = OMX_COLOR_FormatUnused;

  err = OMX_SetParameter(s->handle, OMX_IndexParamPortDefinition,
                         (OMX_PTR) &out_port);
  assert(err == OMX_ErrorNone);

  err = OMX_GetParameter(s->handle, OMX_IndexParamPortDefinition,
                         (OMX_PTR) &out_port);
  assert(err == OMX_ErrorNone);
  s->num_out_bufs = out_port.nBufferCountActual;

  OMX_VIDEO_PARAM_BITRATETYPE bitrate_type = {0};
  bitrate_type.nSize = sizeof(bitrate_type);
  bitrate_type.nPortIndex = (OMX_U32) PORT_INDEX_OUT;
  err = OMX_GetParameter(s->handle, OMX_IndexParamVideoBitrate,
                         (OMX_PTR) &bitrate_type);
  assert(err == OMX_ErrorNone);

  bitrate_type.eControlRate = OMX_Video_ControlRateVariable;
  bitrate_type.nTargetBitrate = bitrate;

  err = OMX_SetParameter(s->handle, OMX_IndexParamVideoBitrate,
                         (OMX_PTR) &bitrate_type);
  assert(err == OMX_ErrorNone);

  if (h265) {
    // setup HEVC
    OMX_VIDEO_PARAM_HEVCTYPE hecv_type = {0};
    hecv_type.nSize = sizeof(hecv_type);
    hecv_type.nPortIndex = (OMX_U32) PORT_INDEX_OUT;
    err = OMX_GetParameter(s->handle, (OMX_INDEXTYPE)OMX_IndexParamVideoHevc,
                           (OMX_PTR) &hecv_type);
    assert(err == OMX_ErrorNone);

    hecv_type.eProfile = OMX_VIDEO_HEVCProfileMain;
    hecv_type.eLevel = OMX_VIDEO_HEVCHighTierLevel5;

    err = OMX_SetParameter(s->handle, (OMX_INDEXTYPE)OMX_IndexParamVideoHevc,
                           (OMX_PTR) &hecv_type);
    assert(err == OMX_ErrorNone);
  } else {
    // setup h264
    OMX_VIDEO_PARAM_AVCTYPE avc = { 0 };
    avc.nSize = sizeof(avc);
    avc.nPortIndex = (OMX_U32) PORT_INDEX_OUT;
    err = OMX_GetParameter(s->handle, OMX_IndexParamVideoAvc, &avc);
    assert(err == OMX_ErrorNone);

    avc.nBFrames = 0;
    avc.nPFrames = 15;

    avc.eProfile = OMX_VIDEO_AVCProfileBaseline;
    avc.eLevel = OMX_VIDEO_AVCLevel31;

    avc.nAllowedPictureTypes |= OMX_VIDEO_PictureTypeB;
    avc.eLoopFilterMode = OMX_VIDEO_AVCLoopFilterEnable;

    err = OMX_SetParameter(s->handle, OMX_IndexParamVideoAvc, &avc);
    assert(err == OMX_ErrorNone);
  }


  // for (int i = 0; ; i++) {
  //   OMX_VIDEO_PARAM_PORTFORMATTYPE video_port_format = {0};
  //   video_port_format.nSize = sizeof(video_port_format);
  //   video_port_format.nIndex = i;
  //   video_port_format.nPortIndex = PORT_INDEX_IN;
  //   if (OMX_GetParameter(s->handle, OMX_IndexParamVideoPortFormat, &video_port_format) != OMX_ErrorNone)
  //       break;
  //   printf("in %d: compression 0x%x format 0x%x %s\n", i,
  //          video_port_format.eCompressionFormat, video_port_format.eColorFormat,
  //          omx_color_fomat_name(video_port_format.eColorFormat));
  // }

  // for (int i=0; i<32; i++) {
  //   OMX_VIDEO_PARAM_PROFILELEVELTYPE params = {0};
  //   params.nSize = sizeof(params);
  //   params.nPortIndex = PORT_INDEX_OUT;
  //   params.nProfileIndex = i;
  //   if (OMX_GetParameter(s->handle, OMX_IndexParamVideoProfileLevelQuerySupported, &params) != OMX_ErrorNone)
  //       break;
  //   printf("profile %d level 0x%x\n", params.eProfile, params.eLevel);
  // }

  err = OMX_SendCommand(s->handle, OMX_CommandStateSet, OMX_StateIdle, NULL);
  assert(err == OMX_ErrorNone);

  s->in_buf_headers = calloc(s->num_in_bufs, sizeof(OMX_BUFFERHEADERTYPE*));
  for (int i=0; i<s->num_in_bufs; i++) {
    err = OMX_AllocateBuffer(s->handle, &s->in_buf_headers[i], PORT_INDEX_IN, s,
                             in_port.nBufferSize);
    assert(err == OMX_ErrorNone);
  }

  s->out_buf_headers = calloc(s->num_out_bufs, sizeof(OMX_BUFFERHEADERTYPE*));
  for (int i=0; i<s->num_out_bufs; i++) {
    err = OMX_AllocateBuffer(s->handle, &s->out_buf_headers[i], PORT_INDEX_OUT, s,
                             out_port.nBufferSize);
    assert(err == OMX_ErrorNone);
  }

  wait_for_state(s, OMX_StateIdle);

  err = OMX_SendCommand(s->handle, OMX_CommandStateSet, OMX_StateExecuting, NULL);
  assert(err == OMX_ErrorNone);

  wait_for_state(s, OMX_StateExecuting);

  // give omx all the output buffers
  for (int i = 0; i < s->num_out_bufs; i++) {
    // printf("fill %p\n", s->out_buf_headers[i]);
    err = OMX_FillThisBuffer(s->handle, s->out_buf_headers[i]);
    assert(err == OMX_ErrorNone);
  }

  // fill the input free queue
  for (int i = 0; i < s->num_in_bufs; i++) {
    queue_push(&s->free_in, (void*)s->in_buf_headers[i]);
  }
}