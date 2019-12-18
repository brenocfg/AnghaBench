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
 int XMONAD ; 
 int XMONAD_FR ; 
 int on_qwerty () ; 

int get_xmonad_layer(){
  int qwerty = on_qwerty();

  if (qwerty)
    return(XMONAD);
  else
    return(XMONAD_FR);
}