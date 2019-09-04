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
typedef  int u32 ;

/* Variables and functions */
 int HASHTABLE_NPAGE ; 
 int HASHTABLE_NPAGE_ONE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int walFramePage(u32 iFrame){
  int iHash = (iFrame+HASHTABLE_NPAGE-HASHTABLE_NPAGE_ONE-1) / HASHTABLE_NPAGE;
  assert( (iHash==0 || iFrame>HASHTABLE_NPAGE_ONE)
       && (iHash>=1 || iFrame<=HASHTABLE_NPAGE_ONE)
       && (iHash<=1 || iFrame>(HASHTABLE_NPAGE_ONE+HASHTABLE_NPAGE))
       && (iHash>=2 || iFrame<=HASHTABLE_NPAGE_ONE+HASHTABLE_NPAGE)
       && (iHash<=2 || iFrame>(HASHTABLE_NPAGE_ONE+2*HASHTABLE_NPAGE))
  );
  return iHash;
}