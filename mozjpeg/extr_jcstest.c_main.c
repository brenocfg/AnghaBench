#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct jpeg_compress_struct {int input_components; int /*<<< orphan*/  in_color_space; int /*<<< orphan*/  err; } ;
struct TYPE_4__ {int /*<<< orphan*/  output_message; int /*<<< orphan*/  error_exit; } ;
struct TYPE_3__ {int /*<<< orphan*/  jb; TYPE_2__ pub; } ;
typedef  TYPE_1__ error_mgr ;

/* Variables and functions */
 int /*<<< orphan*/  JCS_EXT_RGB ; 
 int /*<<< orphan*/  JCS_EXT_RGBA ; 
 int /*<<< orphan*/  jpeg_create_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_default_colorspace (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_destroy_compress (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_set_defaults (struct jpeg_compress_struct*) ; 
 int /*<<< orphan*/  jpeg_std_error (TYPE_2__*) ; 
 char* lasterror ; 
 int /*<<< orphan*/  my_error_exit ; 
 int /*<<< orphan*/  my_output_message ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

int main(void)
{
  int jcs_valid = -1, jcs_alpha_valid = -1;
  struct jpeg_compress_struct cinfo;
  error_mgr jerr;

  printf("libjpeg-turbo colorspace extensions:\n");
#if JCS_EXTENSIONS
  printf("  Present at compile time\n");
#else
  printf("  Not present at compile time\n");
#endif

  cinfo.err = jpeg_std_error(&jerr.pub);
  jerr.pub.error_exit = my_error_exit;
  jerr.pub.output_message = my_output_message;

  if (setjmp(jerr.jb)) {
    /* this will execute if libjpeg has an error */
    jcs_valid = 0;
    goto done;
  }

  jpeg_create_compress(&cinfo);
  cinfo.input_components = 3;
  jpeg_set_defaults(&cinfo);
  cinfo.in_color_space = JCS_EXT_RGB;
  jpeg_default_colorspace(&cinfo);
  jcs_valid = 1;

done:
  if (jcs_valid)
    printf("  Working properly\n");
  else
    printf("  Not working properly.  Error returned was:\n    %s\n",
           lasterror);

  printf("libjpeg-turbo alpha colorspace extensions:\n");
#if JCS_ALPHA_EXTENSIONS
  printf("  Present at compile time\n");
#else
  printf("  Not present at compile time\n");
#endif

  if (setjmp(jerr.jb)) {
    /* this will execute if libjpeg has an error */
    jcs_alpha_valid = 0;
    goto done2;
  }

  cinfo.in_color_space = JCS_EXT_RGBA;
  jpeg_default_colorspace(&cinfo);
  jcs_alpha_valid = 1;

done2:
  if (jcs_alpha_valid)
    printf("  Working properly\n");
  else
    printf("  Not working properly.  Error returned was:\n    %s\n",
           lasterror);

  jpeg_destroy_compress(&cinfo);
  return 0;
}