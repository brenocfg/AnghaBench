#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct msm_ispif_param_data {int num; TYPE_1__* entries; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int num_vfe; } ;
struct ispif_cfg_data {int csid_version; int /*<<< orphan*/  cfg_type; struct msm_ispif_param_data params; TYPE_3__ vfe_info; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  ispif_cfg_data ;
typedef  int /*<<< orphan*/  VisionBuf ;
struct TYPE_15__ {TYPE_2__* ss; } ;
struct TYPE_14__ {scalar_t__ device; TYPE_6__ rear; TYPE_6__ front; void* ispif_fd; } ;
struct TYPE_12__ {int /*<<< orphan*/ * bufs; } ;
struct TYPE_11__ {int vfe_intf; int num_cids; int* cids; int csid; void* intftype; } ;
typedef  TYPE_4__ DualCameraState ;

/* Variables and functions */
 scalar_t__ DEVICE_LP3 ; 
 int /*<<< orphan*/  ISPIF_CFG ; 
 int /*<<< orphan*/  ISPIF_INIT ; 
 int /*<<< orphan*/  ISPIF_SET_VFE_INFO ; 
 int /*<<< orphan*/  ISPIF_START_FRAME_BOUNDARY ; 
 int /*<<< orphan*/  LOG (char*,...) ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 void* RDI0 ; 
 void* RDI1 ; 
 void* RDI2 ; 
 int /*<<< orphan*/  VIDIOC_MSM_ISPIF_CFG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  camera_open (TYPE_6__*,int) ; 
 int /*<<< orphan*/  cameras_close (TYPE_4__*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  front_start (TYPE_6__*) ; 
 scalar_t__ getenv (char*) ; 
 int ioctl (void*,int /*<<< orphan*/ ,struct ispif_cfg_data*) ; 
 int /*<<< orphan*/  memset (struct ispif_cfg_data*,int /*<<< orphan*/ ,int) ; 
 void* open (char*,int) ; 
 int /*<<< orphan*/  rear_start (TYPE_6__*) ; 
 int /*<<< orphan*/  sensors_init (TYPE_4__*) ; 

void cameras_open(DualCameraState *s, VisionBuf *camera_bufs_rear, VisionBuf *camera_bufs_focus, VisionBuf *camera_bufs_stats, VisionBuf *camera_bufs_front) {
  int err;

  struct ispif_cfg_data ispif_cfg_data = {0};

  struct msm_ispif_param_data ispif_params = {0};
  ispif_params.num = 4;
  // rear camera
  ispif_params.entries[0].vfe_intf = 0;
  ispif_params.entries[0].intftype = RDI0;
  ispif_params.entries[0].num_cids = 1;
  ispif_params.entries[0].cids[0] = 0;
  ispif_params.entries[0].csid = 0;
  // front camera
  ispif_params.entries[1].vfe_intf = 1;
  ispif_params.entries[1].intftype = RDI0;
  ispif_params.entries[1].num_cids = 1;
  ispif_params.entries[1].cids[0] = 0;
  ispif_params.entries[1].csid = 2;
  // rear camera (focus)
  ispif_params.entries[2].vfe_intf = 0;
  ispif_params.entries[2].intftype = RDI1;
  ispif_params.entries[2].num_cids = 1;
  ispif_params.entries[2].cids[0] = 1;
  ispif_params.entries[2].csid = 0;
  // rear camera (stats, for AE)
  ispif_params.entries[3].vfe_intf = 0;
  ispif_params.entries[3].intftype = RDI2;
  ispif_params.entries[3].num_cids = 1;
  ispif_params.entries[3].cids[0] = 2;
  ispif_params.entries[3].csid = 0;

  assert(camera_bufs_rear);
  assert(camera_bufs_front);

  int msmcfg_fd = open("/dev/media0", O_RDWR | O_NONBLOCK);
  assert(msmcfg_fd >= 0);

  sensors_init(s);

  int v4l_fd = open("/dev/video0", O_RDWR | O_NONBLOCK);
  assert(v4l_fd >= 0);

  if (s->device == DEVICE_LP3) {
    s->ispif_fd = open("/dev/v4l-subdev15", O_RDWR | O_NONBLOCK);
  } else {
    s->ispif_fd = open("/dev/v4l-subdev16", O_RDWR | O_NONBLOCK);
  }
  assert(s->ispif_fd >= 0);

  // ISPIF: stop
  // memset(&ispif_cfg_data, 0, sizeof(ispif_cfg_data));
  // ispif_cfg_data.cfg_type = ISPIF_STOP_FRAME_BOUNDARY;
  // ispif_cfg_data.params = ispif_params;
  // err = ioctl(s->ispif_fd, VIDIOC_MSM_ISPIF_CFG, &ispif_cfg_data);
  // LOG("ispif stop: %d", err);

  LOG("*** open front ***");
  s->front.ss[0].bufs = camera_bufs_front;
  camera_open(&s->front, false);

  LOG("*** open rear ***");
  s->rear.ss[0].bufs = camera_bufs_rear;
  s->rear.ss[1].bufs = camera_bufs_focus;
  s->rear.ss[2].bufs = camera_bufs_stats;
  camera_open(&s->rear, true);

  if (getenv("CAMERA_TEST")) {
    cameras_close(s);
    exit(0);
  }

  // ISPIF: set vfe info
  memset(&ispif_cfg_data, 0, sizeof(ispif_cfg_data));
  ispif_cfg_data.cfg_type = ISPIF_SET_VFE_INFO;
  ispif_cfg_data.vfe_info.num_vfe = 2;
  err = ioctl(s->ispif_fd, VIDIOC_MSM_ISPIF_CFG, &ispif_cfg_data);
  LOG("ispif set vfe info: %d", err);

  // ISPIF: setup
  memset(&ispif_cfg_data, 0, sizeof(ispif_cfg_data));
  ispif_cfg_data.cfg_type = ISPIF_INIT;
  ispif_cfg_data.csid_version = 0x30050000; //CSID_VERSION_V35
  err = ioctl(s->ispif_fd, VIDIOC_MSM_ISPIF_CFG, &ispif_cfg_data);
  LOG("ispif setup: %d", err);

  memset(&ispif_cfg_data, 0, sizeof(ispif_cfg_data));
  ispif_cfg_data.cfg_type = ISPIF_CFG;
  ispif_cfg_data.params = ispif_params;

  err = ioctl(s->ispif_fd, VIDIOC_MSM_ISPIF_CFG, &ispif_cfg_data);
  LOG("ispif cfg: %d", err);

  ispif_cfg_data.cfg_type = ISPIF_START_FRAME_BOUNDARY;
  err = ioctl(s->ispif_fd, VIDIOC_MSM_ISPIF_CFG, &ispif_cfg_data);
  LOG("ispif start_frame_boundary: %d", err);

  front_start(&s->front);
  rear_start(&s->rear);
}