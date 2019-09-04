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
typedef  int /*<<< orphan*/  arm_feature_set ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_AEXT_V4T ; 
 int /*<<< orphan*/  ARM_ARCH_IWMMXT ; 
 int /*<<< orphan*/  ARM_ARCH_IWMMXT2 ; 
 int /*<<< orphan*/  ARM_ARCH_V2 ; 
 int /*<<< orphan*/  ARM_ARCH_V2S ; 
 int /*<<< orphan*/  ARM_ARCH_V3 ; 
 int /*<<< orphan*/  ARM_ARCH_V3M ; 
 int /*<<< orphan*/  ARM_ARCH_V4 ; 
 int /*<<< orphan*/  ARM_ARCH_V4T ; 
 int /*<<< orphan*/  ARM_ARCH_V5 ; 
 int /*<<< orphan*/  ARM_ARCH_V5T ; 
 int /*<<< orphan*/  ARM_ARCH_V5TE ; 
 int /*<<< orphan*/  ARM_ARCH_XSCALE ; 
 int ARM_CEXT_MAVERICK ; 
 int /*<<< orphan*/  ARM_FEATURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_FEATURE_ALL ; 
 int /*<<< orphan*/  ARM_FEATURE_LOW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ARM_MERGE_FEATURE_SETS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  FPU_FPA ; 
 int FPU_MAVERICK ; 
#define  bfd_mach_arm_2 141 
#define  bfd_mach_arm_2a 140 
#define  bfd_mach_arm_3 139 
#define  bfd_mach_arm_3M 138 
#define  bfd_mach_arm_4 137 
#define  bfd_mach_arm_4T 136 
#define  bfd_mach_arm_5 135 
#define  bfd_mach_arm_5T 134 
#define  bfd_mach_arm_5TE 133 
#define  bfd_mach_arm_XScale 132 
#define  bfd_mach_arm_ep9312 131 
#define  bfd_mach_arm_iWMMXt 130 
#define  bfd_mach_arm_iWMMXt2 129 
#define  bfd_mach_arm_unknown 128 

__attribute__((used)) static void
select_arm_features (unsigned long mach,
		     arm_feature_set * features)
{
#undef ARM_SET_FEATURES2
 //ARM_FEATURE (0, 0, FPU_ARCH_VFP_V4D16) ;	
#define ARM_SET_FEATURES2(FSET) \
  {							\
    const arm_feature_set fset = FSET;			\
    arm_feature_set tmp = FPU_ARCH_VFP_V4D16; \
    ARM_MERGE_FEATURE_SETS (*features, tmp, fset);	\
  }
#undef ARM_SET_FEATURES
#define ARM_SET_FEATURES(FSET) \
  {							\
    const arm_feature_set fset = FSET;			\
    arm_feature_set tmp = ARM_FEATURE (0, 0, FPU_FPA) ;	\
    ARM_MERGE_FEATURE_SETS (*features, tmp, fset);	\
  }

#if 0
//    ARM_SET_FEATURES (ARM_FEATURE_ALL);
ARM_SET_FEATURES2(ARM_ARCH_V7EM); //, FPU_ARCH_VFP_V4D16);
return;
#if 0
FPU_ARCH_VFP_V4D16
return;
#endif
#endif

  switch (mach)
    {
    case bfd_mach_arm_2:       ARM_SET_FEATURES (ARM_ARCH_V2); break;
    case bfd_mach_arm_2a:      ARM_SET_FEATURES (ARM_ARCH_V2S); break;
    case bfd_mach_arm_3:       ARM_SET_FEATURES (ARM_ARCH_V3); break;
    case bfd_mach_arm_3M:      ARM_SET_FEATURES (ARM_ARCH_V3M); break;
    case bfd_mach_arm_4:       ARM_SET_FEATURES (ARM_ARCH_V4); break;
    case bfd_mach_arm_4T:      ARM_SET_FEATURES (ARM_ARCH_V4T); break;
    case bfd_mach_arm_5:       ARM_SET_FEATURES (ARM_ARCH_V5); break;
    case bfd_mach_arm_5T:      ARM_SET_FEATURES (ARM_ARCH_V5T); break;
    case bfd_mach_arm_5TE:     ARM_SET_FEATURES (ARM_ARCH_V5TE); break;
    case bfd_mach_arm_XScale:  ARM_SET_FEATURES (ARM_ARCH_XSCALE); break;
    case bfd_mach_arm_ep9312:
      ARM_SET_FEATURES (ARM_FEATURE_LOW (ARM_AEXT_V4T,
					 ARM_CEXT_MAVERICK | FPU_MAVERICK));
       break;
    case bfd_mach_arm_iWMMXt:  ARM_SET_FEATURES (ARM_ARCH_IWMMXT); break;
    case bfd_mach_arm_iWMMXt2: ARM_SET_FEATURES (ARM_ARCH_IWMMXT2); break;
      /* If the machine type is unknown allow all
	 architecture types and all extensions.  */
    case bfd_mach_arm_unknown: ARM_SET_FEATURES (ARM_FEATURE_ALL); break;
    }

#undef ARM_SET_FEATURES
}