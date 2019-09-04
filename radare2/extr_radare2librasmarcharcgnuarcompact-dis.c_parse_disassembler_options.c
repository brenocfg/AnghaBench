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

/* Variables and functions */
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 int enable_insn_stream ; 
 int enable_simd ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static void
parse_disassembler_options (char *options)
{
  const char *p; 
  for (p = options; p != NULL; )
    {
	  if (CONST_STRNEQ (p, "simd"))
	    {
	      enable_simd = 1;
	    }
	  if (CONST_STRNEQ (p, "insn-stream"))
	    {
		  enable_insn_stream = 1;
	    }
	  
	  p = strchr (p, ',');

	  if (p != NULL) {
		  p++;
	  }
    }
	
}