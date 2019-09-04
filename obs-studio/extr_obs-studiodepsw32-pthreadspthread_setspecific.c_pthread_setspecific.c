#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * p; } ;
struct TYPE_11__ {scalar_t__ keys; int /*<<< orphan*/  threadLock; TYPE_2__ ptHandle; } ;
typedef  TYPE_1__ ptw32_thread_t ;
typedef  int /*<<< orphan*/  ptw32_mcs_local_node_t ;
typedef  TYPE_2__ pthread_t ;
typedef  TYPE_3__* pthread_key_t ;
struct TYPE_14__ {struct TYPE_14__* nextKey; TYPE_3__* key; } ;
typedef  TYPE_4__ ThreadKeyAssoc ;
struct TYPE_13__ {int /*<<< orphan*/  key; int /*<<< orphan*/  keyLock; int /*<<< orphan*/ * destructor; } ;
typedef  int /*<<< orphan*/  LPVOID ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOENT ; 
 int /*<<< orphan*/  TlsSetValue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_getspecific (TYPE_3__*) ; 
 TYPE_2__ pthread_self () ; 
 int /*<<< orphan*/  ptw32_mcs_lock_acquire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptw32_mcs_lock_release (int /*<<< orphan*/ *) ; 
 TYPE_3__* ptw32_selfThreadKey ; 
 int ptw32_tkAssocCreate (TYPE_1__*,TYPE_3__*) ; 

int
pthread_setspecific (pthread_key_t key, const void *value)
     /*
      * ------------------------------------------------------
      * DOCPUBLIC
      *      This function sets the value of the thread specific
      *      key in the calling thread.
      *
      * PARAMETERS
      *      key
      *              an instance of pthread_key_t
      *      value
      *              the value to set key to
      *
      *
      * DESCRIPTION
      *      This function sets the value of the thread specific
      *      key in the calling thread.
      *
      * RESULTS
      *              0               successfully set value
      *              EAGAIN          could not set value
      *              ENOENT          SERIOUS!!
      *
      * ------------------------------------------------------
      */
{
  pthread_t self;
  int result = 0;

  if (key != ptw32_selfThreadKey)
    {
      /*
       * Using pthread_self will implicitly create
       * an instance of pthread_t for the current
       * thread if one wasn't explicitly created
       */
      self = pthread_self ();
      if (self.p == NULL)
	{
	  return ENOENT;
	}
    }
  else
    {
      /*
       * Resolve catch-22 of registering thread with selfThread
       * key
       */
      ptw32_thread_t * sp = (ptw32_thread_t *) pthread_getspecific (ptw32_selfThreadKey);

      if (sp == NULL)
        {
	  if (value == NULL)
	    {
	      return ENOENT;
	    }
          self = *((pthread_t *) value);
        }
      else
        {
	  self = sp->ptHandle;
        }
    }

  result = 0;

  if (key != NULL)
    {
      if (self.p != NULL && key->destructor != NULL && value != NULL)
	{
          ptw32_mcs_local_node_t keyLock;
          ptw32_mcs_local_node_t threadLock;
	  ptw32_thread_t * sp = (ptw32_thread_t *) self.p;
	  /*
	   * Only require associations if we have to
	   * call user destroy routine.
	   * Don't need to locate an existing association
	   * when setting data to NULL for WIN32 since the
	   * data is stored with the operating system; not
	   * on the association; setting assoc to NULL short
	   * circuits the search.
	   */
	  ThreadKeyAssoc *assoc;

	  ptw32_mcs_lock_acquire(&(key->keyLock), &keyLock);
	  ptw32_mcs_lock_acquire(&(sp->threadLock), &threadLock);

	  assoc = (ThreadKeyAssoc *) sp->keys;
	  /*
	   * Locate existing association
	   */
	  while (assoc != NULL)
	    {
	      if (assoc->key == key)
		{
		  /*
		   * Association already exists
		   */
		  break;
		}
		assoc = assoc->nextKey;
	    }

	  /*
	   * create an association if not found
	   */
	  if (assoc == NULL)
	    {
	      result = ptw32_tkAssocCreate (sp, key);
	    }

	  ptw32_mcs_lock_release(&threadLock);
	  ptw32_mcs_lock_release(&keyLock);
	}

      if (result == 0)
	{
	  if (!TlsSetValue (key->key, (LPVOID) value))
	    {
	      result = EAGAIN;
	    }
	}
    }

  return (result);
}