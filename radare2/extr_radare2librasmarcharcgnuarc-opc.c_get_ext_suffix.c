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
struct arc_operand_value {char type; int /*<<< orphan*/  name; } ;
struct arc_ext_operand_value {struct arc_ext_operand_value* next; struct arc_operand_value operand; } ;

/* Variables and functions */
 char ADDRESS12 ; 
 char ADDRESS22S_AC ; 
 char ADDRESS22_AC ; 
 char ADDRESS24 ; 
 char ADDRESS3 ; 
 char ADDRESS3_AC ; 
 char ADDRESS9_AC ; 
 char CACHEBYPASS11_AC ; 
 char CACHEBYPASS14 ; 
 char CACHEBYPASS15_AC ; 
 char CACHEBYPASS26 ; 
 char CACHEBYPASS5 ; 
 char CACHEBYPASS5_AC ; 
 char COND ; 
 char COND_AC ; 
 char FLAG ; 
 char FLAG_AC ; 
 char JUMPFLAGS ; 
 char SIGN0 ; 
 char SIGN16_AC ; 
 char SIGN6_AC ; 
 char SIGN9 ; 
 char SIZE1 ; 
 char SIZE10 ; 
 char SIZE17_AC ; 
 char SIZE1_AC ; 
 char SIZE22 ; 
 char SIZE7_AC ; 
 struct arc_ext_operand_value* arc_ext_operands ; 
 scalar_t__ arc_mach_a4 ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

struct arc_operand_value *
get_ext_suffix (char *s, char field)
{
  struct arc_ext_operand_value *suffix = arc_ext_operands;
  char ctype = 0;

  switch(field){
  case 'e' :
      ctype = arc_mach_a4 ? CACHEBYPASS5 : 0;
      break;
  case 'f' :
      ctype = arc_mach_a4 ? FLAG : FLAG_AC;
      break;
  case 'j' :
      ctype = arc_mach_a4 ? JUMPFLAGS : 0;
      break;
  case 'p' :
      ctype = arc_mach_a4 ? 0 : ADDRESS9_AC;
      break;
  case 'q' :
      ctype = arc_mach_a4 ? COND : COND_AC;
      break;
  case 't' :
      ctype = arc_mach_a4 ? 0 : SIZE7_AC;
      break;
  case 'v' :
      ctype = arc_mach_a4 ? ADDRESS24 : CACHEBYPASS11_AC;
      break;
  case 'w' :
      ctype = arc_mach_a4 ? ADDRESS3 : ADDRESS3_AC;
      break;
  case 'x' :
      ctype = arc_mach_a4 ? SIGN0 : SIGN6_AC;
      break;
  case 'y' :
      ctype = arc_mach_a4 ? SIZE22 : 0;
      break;
  case 'z' :
      ctype = arc_mach_a4 ? SIZE1 : SIZE1_AC;
      break;
  case 'D' :
      ctype = arc_mach_a4 ? CACHEBYPASS26 : CACHEBYPASS5_AC;
      break;
  case 'E' :
      ctype = arc_mach_a4 ? CACHEBYPASS14 : 0;
      break;
  case 'P' :
      ctype = arc_mach_a4 ? 0 : ADDRESS22_AC;
      break;
  case 'T' :
      ctype = arc_mach_a4 ? 0 : SIZE17_AC;
      break;
  case 'V' :
      ctype = arc_mach_a4 ? 0 : CACHEBYPASS15_AC;
      break;
  case 'W' :
      ctype = arc_mach_a4 ? ADDRESS12 : 0;
      break;
  case 'X' :
      ctype = arc_mach_a4 ? SIGN9 : SIGN16_AC;
      break;
  case 'Z' :
      ctype = arc_mach_a4 ? SIZE10 : 0;
      break;
  case '&' :
      ctype = arc_mach_a4 ? 0 : ADDRESS22S_AC;
      break;
  default :
      ctype = arc_mach_a4 ? COND : COND_AC;
      break;
      } /* end switch(field) */
      if (ctype == 0) {
	      ctype = arc_mach_a4 ? COND : COND_AC;
      }
      while (suffix) {
	      if ((suffix->operand.type == ctype) && !strcmp (s, suffix->operand.name)) {
		      return (&suffix->operand);
	      }
	      suffix = suffix->next;
  } /* end while(suffix) */

  return NULL;
}