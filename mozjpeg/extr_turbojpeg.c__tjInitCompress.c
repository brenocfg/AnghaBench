#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  err; } ;
struct TYPE_10__ {int /*<<< orphan*/  last_addon_message; int /*<<< orphan*/  first_addon_message; int /*<<< orphan*/  addon_message_table; int /*<<< orphan*/  emit_message; int /*<<< orphan*/  output_message; int /*<<< orphan*/  error_exit; } ;
struct TYPE_8__ {int /*<<< orphan*/  setjmp_buffer; TYPE_3__ pub; int /*<<< orphan*/  emit_message; } ;
struct TYPE_9__ {int /*<<< orphan*/  init; TYPE_4__ cinfo; TYPE_1__ jerr; } ;
typedef  TYPE_2__ tjinstance ;
typedef  int /*<<< orphan*/ * tjhandle ;

/* Variables and functions */
 int /*<<< orphan*/  COMPRESS ; 
 int /*<<< orphan*/  JMSG_FIRSTADDONCODE ; 
 int /*<<< orphan*/  JMSG_LASTADDONCODE ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  jpeg_create_compress (TYPE_4__*) ; 
 int /*<<< orphan*/  jpeg_mem_dest_tj (TYPE_4__*,unsigned char**,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jpeg_std_error (TYPE_3__*) ; 
 int /*<<< orphan*/  my_emit_message ; 
 int /*<<< orphan*/  my_error_exit ; 
 int /*<<< orphan*/  my_output_message ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  turbojpeg_message_table ; 

__attribute__((used)) static tjhandle _tjInitCompress(tjinstance *this)
{
	static unsigned char buffer[1];
  unsigned char *buf = buffer;
  unsigned long size = 1;

  /* This is also straight out of example.txt */
	this->cinfo.err=jpeg_std_error(&this->jerr.pub);
	this->jerr.pub.error_exit=my_error_exit;
	this->jerr.pub.output_message=my_output_message;
	this->jerr.emit_message=this->jerr.pub.emit_message;
	this->jerr.pub.emit_message=my_emit_message;
  this->jerr.pub.addon_message_table = turbojpeg_message_table;
  this->jerr.pub.first_addon_message = JMSG_FIRSTADDONCODE;
  this->jerr.pub.last_addon_message = JMSG_LASTADDONCODE;

  if (setjmp(this->jerr.setjmp_buffer)) {
		/* If we get here, the JPEG code has signaled an error. */
		if(this) free(this);
		return NULL;
	}

	jpeg_create_compress(&this->cinfo);
	/* Make an initial call so it will create the destination manager */
	jpeg_mem_dest_tj(&this->cinfo, &buf, &size, 0);

	this->init|=COMPRESS;
	return (tjhandle)this;
}