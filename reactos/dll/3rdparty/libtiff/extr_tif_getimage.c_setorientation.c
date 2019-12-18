#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int orientation; int req_orientation; } ;
typedef  TYPE_1__ TIFFRGBAImage ;

/* Variables and functions */
 int FLIP_HORIZONTALLY ; 
 int FLIP_VERTICALLY ; 
#define  ORIENTATION_BOTLEFT 135 
#define  ORIENTATION_BOTRIGHT 134 
#define  ORIENTATION_LEFTBOT 133 
#define  ORIENTATION_LEFTTOP 132 
#define  ORIENTATION_RIGHTBOT 131 
#define  ORIENTATION_RIGHTTOP 130 
#define  ORIENTATION_TOPLEFT 129 
#define  ORIENTATION_TOPRIGHT 128 

__attribute__((used)) static int 
setorientation(TIFFRGBAImage* img)
{
	switch (img->orientation) {
		case ORIENTATION_TOPLEFT:
		case ORIENTATION_LEFTTOP:
			if (img->req_orientation == ORIENTATION_TOPRIGHT ||
			    img->req_orientation == ORIENTATION_RIGHTTOP)
				return FLIP_HORIZONTALLY;
			else if (img->req_orientation == ORIENTATION_BOTRIGHT ||
			    img->req_orientation == ORIENTATION_RIGHTBOT)
				return FLIP_HORIZONTALLY | FLIP_VERTICALLY;
			else if (img->req_orientation == ORIENTATION_BOTLEFT ||
			    img->req_orientation == ORIENTATION_LEFTBOT)
				return FLIP_VERTICALLY;
			else
				return 0;
		case ORIENTATION_TOPRIGHT:
		case ORIENTATION_RIGHTTOP:
			if (img->req_orientation == ORIENTATION_TOPLEFT ||
			    img->req_orientation == ORIENTATION_LEFTTOP)
				return FLIP_HORIZONTALLY;
			else if (img->req_orientation == ORIENTATION_BOTRIGHT ||
			    img->req_orientation == ORIENTATION_RIGHTBOT)
				return FLIP_VERTICALLY;
			else if (img->req_orientation == ORIENTATION_BOTLEFT ||
			    img->req_orientation == ORIENTATION_LEFTBOT)
				return FLIP_HORIZONTALLY | FLIP_VERTICALLY;
			else
				return 0;
		case ORIENTATION_BOTRIGHT:
		case ORIENTATION_RIGHTBOT:
			if (img->req_orientation == ORIENTATION_TOPLEFT ||
			    img->req_orientation == ORIENTATION_LEFTTOP)
				return FLIP_HORIZONTALLY | FLIP_VERTICALLY;
			else if (img->req_orientation == ORIENTATION_TOPRIGHT ||
			    img->req_orientation == ORIENTATION_RIGHTTOP)
				return FLIP_VERTICALLY;
			else if (img->req_orientation == ORIENTATION_BOTLEFT ||
			    img->req_orientation == ORIENTATION_LEFTBOT)
				return FLIP_HORIZONTALLY;
			else
				return 0;
		case ORIENTATION_BOTLEFT:
		case ORIENTATION_LEFTBOT:
			if (img->req_orientation == ORIENTATION_TOPLEFT ||
			    img->req_orientation == ORIENTATION_LEFTTOP)
				return FLIP_VERTICALLY;
			else if (img->req_orientation == ORIENTATION_TOPRIGHT ||
			    img->req_orientation == ORIENTATION_RIGHTTOP)
				return FLIP_HORIZONTALLY | FLIP_VERTICALLY;
			else if (img->req_orientation == ORIENTATION_BOTRIGHT ||
			    img->req_orientation == ORIENTATION_RIGHTBOT)
				return FLIP_HORIZONTALLY;
			else
				return 0;
		default:	/* NOTREACHED */
			return 0;
	}
}