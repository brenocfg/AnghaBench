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
typedef  TYPE_1__* pthread_barrierattr_t ;
struct TYPE_3__ {int /*<<< orphan*/  pshared; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PTHREAD_PROCESS_PRIVATE ; 
 scalar_t__ calloc (int,int) ; 

int
pthread_barrierattr_init (pthread_barrierattr_t * attr)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      Initializes a barrier attributes object with default
      *      attributes.
      *
      * PARAMETERS
      *      attr
      *              pointer to an instance of pthread_barrierattr_t
      *
      *
      * DESCRIPTION
      *      Initializes a barrier attributes object with default
      *      attributes.
      *
      *      NOTES:
      *              1)      Used to define barrier types
      *
      * RESULTS
      *              0               successfully initialized attr,
      *              ENOMEM          insufficient memory for attr.
      *
      * ------------------------------------------------------
      */
{
  pthread_barrierattr_t ba;
  int result = 0;

  ba = (pthread_barrierattr_t) calloc (1, sizeof (*ba));

  if (ba == NULL)
    {
      result = ENOMEM;
    }
  else
    {
      ba->pshared = PTHREAD_PROCESS_PRIVATE;
    }

  *attr = ba;

  return (result);
}