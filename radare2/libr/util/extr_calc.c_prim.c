#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int curr_tok; void* number_value; int /*<<< orphan*/  string_value; } ;
typedef  void* RNumCalcValue ;
typedef  TYPE_1__ RNumCalc ;
typedef  int /*<<< orphan*/  RNum ;

/* Variables and functions */
 void* Naddi (void*,int) ; 
 void* Nneg (void*) ; 
 void* Norr (void*,void*) ; 
 void* Nset (int /*<<< orphan*/ ) ; 
 void* Nsub (void*,void*) ; 
 int /*<<< orphan*/  Nsubi (void*,int) ; 
#define  RNCAND 149 
#define  RNCASSIGN 148 
#define  RNCDEC 147 
#define  RNCDIV 146 
#define  RNCEND 145 
#define  RNCINC 144 
#define  RNCLEFTP 143 
#define  RNCMINUS 142 
#define  RNCMOD 141 
#define  RNCMUL 140 
#define  RNCNAME 139 
#define  RNCNEG 138 
#define  RNCNUMBER 137 
#define  RNCORR 136 
#define  RNCPLUS 135 
#define  RNCPRINT 134 
#define  RNCRIGHTP 133 
#define  RNCROL 132 
#define  RNCROR 131 
#define  RNCSHL 130 
#define  RNCSHR 129 
#define  RNCXOR 128 
 int /*<<< orphan*/  error (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 void* expr (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  get_token (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  r_num_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_str_trim (int /*<<< orphan*/ ) ; 

__attribute__((used)) static RNumCalcValue prim(RNum *num, RNumCalc *nc, int get) {
	RNumCalcValue v = {0};
	if (get) {
		get_token (num, nc);
	}
	switch (nc->curr_tok) {
	case RNCNUMBER:
		v = nc->number_value;
		get_token (num, nc);
		return v;
	case RNCNAME:
		//fprintf (stderr, "error: unknown keyword (%s)\n", nc->string_value);
		//double& v = table[nc->string_value];
		r_str_trim (nc->string_value);
		v = Nset (r_num_get (num, nc->string_value));
		get_token (num, nc);
		if (nc->curr_tok  == RNCASSIGN) {
			v = expr (num, nc, 1);
		}
		if (nc->curr_tok == RNCINC) {
			Naddi (v, 1);
		}
		if (nc->curr_tok == RNCDEC) {
			Nsubi (v, 1);
		}
		return v;
	case RNCNEG:
		get_token (num, nc);
		return Nneg (nc->number_value); //prim (num, nc, 1), 1);
	case RNCINC:
		return Naddi (prim (num, nc, 1), 1);
	case RNCDEC:
		return Naddi (prim (num, nc, 1), -1);
	case RNCORR:
		return Norr (v, prim (num, nc, 1));
	case RNCMINUS:
		return Nsub (v, prim (num, nc, 1));
	case RNCLEFTP:
		v = expr (num, nc, 1);
		if (nc->curr_tok == RNCRIGHTP) {
			get_token (num, nc);
		} else {
			error (num, nc, " ')' expected");
		}
	case RNCEND:
	case RNCXOR:
	case RNCAND:
	case RNCPLUS:
	case RNCMOD:
	case RNCMUL:
	case RNCDIV:
	case RNCPRINT:
	case RNCASSIGN:
	case RNCRIGHTP:
	case RNCSHL:
	case RNCSHR:
	case RNCROL:
	case RNCROR:
		return v;
	//default: error (num, nc, "primary expected");
	}
	return v;
}