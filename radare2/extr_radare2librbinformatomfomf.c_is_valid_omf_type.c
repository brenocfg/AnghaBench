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
typedef  scalar_t__ ut8 ;

/* Variables and functions */
 scalar_t__ OMF_ALIAS ; 
 scalar_t__ OMF_BAKPAT ; 
 scalar_t__ OMF_BAKPAT32 ; 
 scalar_t__ OMF_CEXTDEF ; 
 scalar_t__ OMF_COMDAT ; 
 scalar_t__ OMF_COMDAT32 ; 
 scalar_t__ OMF_COMDEF ; 
 scalar_t__ OMF_COMENT ; 
 scalar_t__ OMF_EXTDEF ; 
 scalar_t__ OMF_FIXUPP ; 
 scalar_t__ OMF_FIXUPP32 ; 
 scalar_t__ OMF_GRPDEF ; 
 scalar_t__ OMF_LCOMDEF ; 
 scalar_t__ OMF_LEDATA ; 
 scalar_t__ OMF_LEDATA32 ; 
 scalar_t__ OMF_LEXTDEF ; 
 scalar_t__ OMF_LHEADR ; 
 scalar_t__ OMF_LIDATA ; 
 scalar_t__ OMF_LIDATA32 ; 
 scalar_t__ OMF_LINNUM ; 
 scalar_t__ OMF_LINNUM32 ; 
 scalar_t__ OMF_LINSYM ; 
 scalar_t__ OMF_LINSYM32 ; 
 scalar_t__ OMF_LLNAMES ; 
 scalar_t__ OMF_LNAMES ; 
 scalar_t__ OMF_LPUBDEF ; 
 scalar_t__ OMF_LPUBDEF32 ; 
 scalar_t__ OMF_MODEND ; 
 scalar_t__ OMF_MODEND32 ; 
 scalar_t__ OMF_NBKPAT ; 
 scalar_t__ OMF_NBKPAT32 ; 
 scalar_t__ OMF_PUBDEF ; 
 scalar_t__ OMF_PUBDEF32 ; 
 scalar_t__ OMF_SEGDEF ; 
 scalar_t__ OMF_SEGDEF32 ; 
 scalar_t__ OMF_THEADR ; 
 scalar_t__ OMF_VENDEXT ; 
 scalar_t__ OMF_VERNUM ; 

__attribute__((used)) static int is_valid_omf_type(ut8 type) {
	int ct = 0;
	ut8 types[] = {
		OMF_THEADR, OMF_LHEADR, OMF_COMENT, OMF_MODEND, OMF_MODEND32,
		OMF_EXTDEF, OMF_PUBDEF, OMF_PUBDEF32, OMF_LINNUM,
		OMF_LINNUM32, OMF_LNAMES, OMF_LNAMES, OMF_SEGDEF,
		OMF_SEGDEF32, OMF_GRPDEF, OMF_FIXUPP, OMF_FIXUPP32,
		OMF_LEDATA, OMF_LEDATA32, OMF_LIDATA, OMF_LIDATA32,
		OMF_COMDEF, OMF_BAKPAT, OMF_BAKPAT32, OMF_LEXTDEF,
		OMF_LPUBDEF, OMF_LPUBDEF32, OMF_LCOMDEF, OMF_CEXTDEF,
		OMF_COMDAT, OMF_COMDAT32, OMF_LINSYM, OMF_LINSYM32,
		OMF_ALIAS, OMF_NBKPAT, OMF_NBKPAT32, OMF_LLNAMES, OMF_VERNUM,
		OMF_VENDEXT, 0};
	for (; types[ct]; ct++) {
		if (type == types[ct]) {
			return true;
		}
	}
	// eprintf ("Invalid record type\n");
	return false;
}