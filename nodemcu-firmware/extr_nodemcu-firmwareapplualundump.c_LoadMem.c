#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ swap; } ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  IF (int,char*) ; 
 int /*<<< orphan*/  LoadBlock (TYPE_1__*,void*,int) ; 

__attribute__((used)) static void LoadMem (LoadState* S, void* b, int n, size_t size)
{
  LoadBlock(S,b,n*size);
  if (S->swap && b)
  {
    char* p=(char*) b;
    char c;
    switch (size)
    {
      case 1:
        break;
      case 2:
	      while (n--)
	      {
	        c=p[0]; p[0]=p[1]; p[1]=c;
	        p+=2;
	      }
  	    break;
      case 4:
	      while (n--)
	      {
	        c=p[0]; p[0]=p[3]; p[3]=c;
	        c=p[1]; p[1]=p[2]; p[2]=c;
	        p+=4;
	      }
  	    break;
      case 8:
	      while (n--)
	      {
          c=p[0]; p[0]=p[7]; p[7]=c;
          c=p[1]; p[1]=p[6]; p[6]=c;
          c=p[2]; p[2]=p[5]; p[5]=c;
          c=p[3]; p[3]=p[4]; p[4]=c;
          p+=8;
        }
  	    break;
      default:
   	    IF(1, "bad size");
  	    break;
    }
  }
}