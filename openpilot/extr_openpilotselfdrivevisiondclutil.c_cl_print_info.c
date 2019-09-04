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
typedef  int /*<<< orphan*/  type ;
typedef  int /*<<< orphan*/  sz ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  cl_platform_id ;
typedef  int cl_device_type ;
typedef  int /*<<< orphan*/  cl_device_id ;

/* Variables and functions */
 int /*<<< orphan*/  CL_DEVICE_MAX_WORK_GROUP_SIZE ; 
 int /*<<< orphan*/  CL_DEVICE_NAME ; 
 int /*<<< orphan*/  CL_DEVICE_TYPE ; 
#define  CL_DEVICE_TYPE_ACCELERATOR 130 
#define  CL_DEVICE_TYPE_CPU 129 
#define  CL_DEVICE_TYPE_GPU 128 
 int /*<<< orphan*/  CL_DEVICE_VERSION ; 
 int /*<<< orphan*/  CL_PLATFORM_EXTENSIONS ; 
 int /*<<< orphan*/  CL_PLATFORM_PROFILE ; 
 int /*<<< orphan*/  CL_PLATFORM_VENDOR ; 
 int /*<<< orphan*/  clGetDeviceInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  clGetPlatformInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_version_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void cl_print_info(cl_platform_id platform, cl_device_id device) {
  char str[4096];

  clGetPlatformInfo(platform, CL_PLATFORM_VENDOR, sizeof(str), str, NULL);
  printf("vendor: '%s'\n", str);

  char* version = get_version_string(platform);
  printf("platform version: '%s'\n", version);
  free(version);

  clGetPlatformInfo(platform, CL_PLATFORM_PROFILE, sizeof(str), str, NULL);
  printf("profile: '%s'\n", str);

  clGetPlatformInfo(platform, CL_PLATFORM_EXTENSIONS, sizeof(str), str, NULL);
  printf("extensions: '%s'\n", str);

  clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(str), str, NULL);
  printf("name: '%s'\n", str);

  clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(str), str, NULL);
  printf("device version: '%s'\n", str);

  size_t sz;
  clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(sz), &sz, NULL);
  printf("max work group size: %u\n", sz);

  cl_device_type type;
  clGetDeviceInfo(device, CL_DEVICE_TYPE, sizeof(type), &type, NULL);
  printf("type = 0x%04x = ", (unsigned int)type);
  switch(type) {
  case CL_DEVICE_TYPE_CPU:
    printf("CL_DEVICE_TYPE_CPU\n");
    break;
  case CL_DEVICE_TYPE_GPU:
    printf("CL_DEVICE_TYPE_GPU\n");
    break;
  case CL_DEVICE_TYPE_ACCELERATOR:
    printf("CL_DEVICE_TYPE_ACCELERATOR\n");
    break;
  default:
    printf("Other...\n" );
    break;
  }
}