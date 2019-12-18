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
typedef  scalar_t__ SOCKET ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closesocket (scalar_t__) ; 
 scalar_t__ connected ; 
 scalar_t__ proxflag ; 
 int /*<<< orphan*/  pswitch (int) ; 
 int /*<<< orphan*/  shutdown (int,int) ; 

void lostpeer(void)
{
   extern SOCKET cout;
   extern int data;

   if (connected) {
      if (cout) {
         closesocket(cout);
         cout = 0;
      }
      if (data >= 0) {
         (void) shutdown(data, 1+1);
         (void) close(data);
         data = -1;
      }
      connected = 0;
   }
   pswitch(1);
   if (connected) {
      if (cout) {
						closesocket(cout);
         cout = 0;
      }
      connected = 0;
   }
   proxflag = 0;
   pswitch(0);
}