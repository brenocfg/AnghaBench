#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_23__ ;
typedef  struct TYPE_37__   TYPE_22__ ;
typedef  struct TYPE_36__   TYPE_21__ ;
typedef  struct TYPE_35__   TYPE_20__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_19__ ;
typedef  struct TYPE_32__   TYPE_18__ ;
typedef  struct TYPE_31__   TYPE_17__ ;
typedef  struct TYPE_30__   TYPE_16__ ;
typedef  struct TYPE_29__   TYPE_15__ ;
typedef  struct TYPE_28__   TYPE_14__ ;
typedef  struct TYPE_27__   TYPE_13__ ;
typedef  struct TYPE_26__   TYPE_12__ ;
typedef  struct TYPE_25__   TYPE_11__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_34__ {int /*<<< orphan*/  group; } ;
struct f_uvc_opts {TYPE_1__ func_inst; } ;
struct TYPE_46__ {int /*<<< orphan*/  group; } ;
struct TYPE_45__ {int /*<<< orphan*/  group; } ;
struct TYPE_44__ {int /*<<< orphan*/  group; } ;
struct TYPE_43__ {int /*<<< orphan*/  group; } ;
struct TYPE_42__ {int /*<<< orphan*/  group; } ;
struct TYPE_41__ {int /*<<< orphan*/  group; } ;
struct TYPE_40__ {int /*<<< orphan*/  group; } ;
struct TYPE_39__ {int /*<<< orphan*/  group; } ;
struct TYPE_38__ {int /*<<< orphan*/  group; } ;
struct TYPE_37__ {int /*<<< orphan*/  group; } ;
struct TYPE_36__ {int /*<<< orphan*/  group; } ;
struct TYPE_35__ {int /*<<< orphan*/  group; } ;
struct TYPE_33__ {int /*<<< orphan*/  group; } ;
struct TYPE_32__ {int /*<<< orphan*/  group; } ;
struct TYPE_31__ {int /*<<< orphan*/  group; } ;
struct TYPE_30__ {int /*<<< orphan*/  group; } ;
struct TYPE_29__ {int /*<<< orphan*/  group; } ;
struct TYPE_28__ {int /*<<< orphan*/  group; } ;
struct TYPE_27__ {int /*<<< orphan*/  group; } ;
struct TYPE_26__ {int /*<<< orphan*/  group; } ;
struct TYPE_25__ {int /*<<< orphan*/  group; } ;
struct TYPE_24__ {int /*<<< orphan*/  group; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uvc_func_type ; 
 TYPE_23__ uvcg_camera_grp ; 
 int /*<<< orphan*/  uvcg_camera_grp_type ; 
 TYPE_22__ uvcg_color_matching_grp ; 
 int /*<<< orphan*/  uvcg_color_matching_grp_type ; 
 TYPE_21__ uvcg_control_class_fs ; 
 TYPE_20__ uvcg_control_class_grp ; 
 int /*<<< orphan*/  uvcg_control_class_grp_type ; 
 TYPE_19__ uvcg_control_class_ss ; 
 int /*<<< orphan*/  uvcg_control_class_type ; 
 TYPE_18__ uvcg_control_grp ; 
 int /*<<< orphan*/  uvcg_control_grp_type ; 
 TYPE_17__ uvcg_control_header_grp ; 
 int /*<<< orphan*/  uvcg_control_header_grp_type ; 
 TYPE_16__ uvcg_default_camera ; 
 int /*<<< orphan*/  uvcg_default_camera_type ; 
 TYPE_15__ uvcg_default_color_matching ; 
 int /*<<< orphan*/  uvcg_default_color_matching_type ; 
 TYPE_14__ uvcg_default_output ; 
 int /*<<< orphan*/  uvcg_default_output_type ; 
 TYPE_13__ uvcg_default_processing ; 
 int /*<<< orphan*/  uvcg_default_processing_type ; 
 TYPE_12__ uvcg_mjpeg_grp ; 
 int /*<<< orphan*/  uvcg_mjpeg_grp_type ; 
 TYPE_11__ uvcg_output_grp ; 
 int /*<<< orphan*/  uvcg_output_grp_type ; 
 TYPE_10__ uvcg_processing_grp ; 
 int /*<<< orphan*/  uvcg_processing_grp_type ; 
 TYPE_9__ uvcg_streaming_class_fs ; 
 TYPE_8__ uvcg_streaming_class_grp ; 
 int /*<<< orphan*/  uvcg_streaming_class_grp_type ; 
 TYPE_7__ uvcg_streaming_class_hs ; 
 TYPE_6__ uvcg_streaming_class_ss ; 
 int /*<<< orphan*/  uvcg_streaming_class_type ; 
 TYPE_5__ uvcg_streaming_grp ; 
 int /*<<< orphan*/  uvcg_streaming_grp_type ; 
 TYPE_4__ uvcg_streaming_header_grp ; 
 int /*<<< orphan*/  uvcg_streaming_header_grp_type ; 
 TYPE_3__ uvcg_terminal_grp ; 
 int /*<<< orphan*/  uvcg_terminal_grp_type ; 
 TYPE_2__ uvcg_uncompressed_grp ; 
 int /*<<< orphan*/  uvcg_uncompressed_grp_type ; 

int uvcg_attach_configfs(struct f_uvc_opts *opts)
{
	config_group_init_type_name(&uvcg_control_header_grp.group,
				    "header",
				    &uvcg_control_header_grp_type);

	config_group_init_type_name(&uvcg_default_processing.group,
			"default", &uvcg_default_processing_type);
	config_group_init_type_name(&uvcg_processing_grp.group,
			"processing", &uvcg_processing_grp_type);
	configfs_add_default_group(&uvcg_default_processing.group,
			&uvcg_processing_grp.group);

	config_group_init_type_name(&uvcg_default_camera.group,
			"default", &uvcg_default_camera_type);
	config_group_init_type_name(&uvcg_camera_grp.group,
			"camera", &uvcg_camera_grp_type);
	configfs_add_default_group(&uvcg_default_camera.group,
			&uvcg_camera_grp.group);

	config_group_init_type_name(&uvcg_default_output.group,
			"default", &uvcg_default_output_type);
	config_group_init_type_name(&uvcg_output_grp.group,
			"output", &uvcg_output_grp_type);
	configfs_add_default_group(&uvcg_default_output.group,
			&uvcg_output_grp.group);

	config_group_init_type_name(&uvcg_terminal_grp.group,
			"terminal", &uvcg_terminal_grp_type);
	configfs_add_default_group(&uvcg_camera_grp.group,
			&uvcg_terminal_grp.group);
	configfs_add_default_group(&uvcg_output_grp.group,
			&uvcg_terminal_grp.group);

	config_group_init_type_name(&uvcg_control_class_fs.group,
			"fs", &uvcg_control_class_type);
	config_group_init_type_name(&uvcg_control_class_ss.group,
			"ss", &uvcg_control_class_type);
	config_group_init_type_name(&uvcg_control_class_grp.group,
			"class",
			&uvcg_control_class_grp_type);
	configfs_add_default_group(&uvcg_control_class_fs.group,
			&uvcg_control_class_grp.group);
	configfs_add_default_group(&uvcg_control_class_ss.group,
			&uvcg_control_class_grp.group);

	config_group_init_type_name(&uvcg_control_grp.group,
			"control",
			&uvcg_control_grp_type);
	configfs_add_default_group(&uvcg_control_header_grp.group,
			&uvcg_control_grp.group);
	configfs_add_default_group(&uvcg_processing_grp.group,
			&uvcg_control_grp.group);
	configfs_add_default_group(&uvcg_terminal_grp.group,
			&uvcg_control_grp.group);
	configfs_add_default_group(&uvcg_control_class_grp.group,
			&uvcg_control_grp.group);

	config_group_init_type_name(&uvcg_streaming_header_grp.group,
				    "header",
				    &uvcg_streaming_header_grp_type);
	config_group_init_type_name(&uvcg_uncompressed_grp.group,
				    "uncompressed",
				    &uvcg_uncompressed_grp_type);
	config_group_init_type_name(&uvcg_mjpeg_grp.group,
				    "mjpeg",
				    &uvcg_mjpeg_grp_type);
	config_group_init_type_name(&uvcg_default_color_matching.group,
				    "default",
				    &uvcg_default_color_matching_type);
	config_group_init_type_name(&uvcg_color_matching_grp.group,
			"color_matching",
			&uvcg_color_matching_grp_type);
	configfs_add_default_group(&uvcg_default_color_matching.group,
			&uvcg_color_matching_grp.group);

	config_group_init_type_name(&uvcg_streaming_class_fs.group,
			"fs", &uvcg_streaming_class_type);
	config_group_init_type_name(&uvcg_streaming_class_hs.group,
			"hs", &uvcg_streaming_class_type);
	config_group_init_type_name(&uvcg_streaming_class_ss.group,
			"ss", &uvcg_streaming_class_type);
	config_group_init_type_name(&uvcg_streaming_class_grp.group,
			"class", &uvcg_streaming_class_grp_type);
	configfs_add_default_group(&uvcg_streaming_class_fs.group,
			&uvcg_streaming_class_grp.group);
	configfs_add_default_group(&uvcg_streaming_class_hs.group,
			&uvcg_streaming_class_grp.group);
	configfs_add_default_group(&uvcg_streaming_class_ss.group,
			&uvcg_streaming_class_grp.group);

	config_group_init_type_name(&uvcg_streaming_grp.group,
			"streaming", &uvcg_streaming_grp_type);
	configfs_add_default_group(&uvcg_streaming_header_grp.group,
			&uvcg_streaming_grp.group);
	configfs_add_default_group(&uvcg_uncompressed_grp.group,
			&uvcg_streaming_grp.group);
	configfs_add_default_group(&uvcg_mjpeg_grp.group,
			&uvcg_streaming_grp.group);
	configfs_add_default_group(&uvcg_color_matching_grp.group,
			&uvcg_streaming_grp.group);
	configfs_add_default_group(&uvcg_streaming_class_grp.group,
			&uvcg_streaming_grp.group);

	config_group_init_type_name(&opts->func_inst.group,
			"",
			&uvc_func_type);
	configfs_add_default_group(&uvcg_control_grp.group,
			&opts->func_inst.group);
	configfs_add_default_group(&uvcg_streaming_grp.group,
			&opts->func_inst.group);

	return 0;
}