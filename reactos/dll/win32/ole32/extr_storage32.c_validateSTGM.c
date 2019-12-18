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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int STGM_ACCESS_MODE (int) ; 
 int STGM_CONVERT ; 
#define  STGM_CREATE 136 
 int STGM_CREATE_MODE (int) ; 
#define  STGM_FAILIFTHERE 135 
 int STGM_KNOWN_FLAGS ; 
 int STGM_NOSCRATCH ; 
 int STGM_NOSNAPSHOT ; 
#define  STGM_READ 134 
#define  STGM_READWRITE 133 
#define  STGM_SHARE_DENY_NONE 132 
#define  STGM_SHARE_DENY_READ 131 
#define  STGM_SHARE_DENY_WRITE 130 
#define  STGM_SHARE_EXCLUSIVE 129 
 int STGM_SHARE_MODE (int) ; 
 int STGM_SIMPLE ; 
 int STGM_TRANSACTED ; 
#define  STGM_WRITE 128 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT validateSTGM(DWORD stgm)
{
  DWORD access = STGM_ACCESS_MODE(stgm);
  DWORD share  = STGM_SHARE_MODE(stgm);
  DWORD create = STGM_CREATE_MODE(stgm);

  if (stgm&~STGM_KNOWN_FLAGS)
  {
    ERR("unknown flags %08x\n", stgm);
    return E_FAIL;
  }

  switch (access)
  {
  case STGM_READ:
  case STGM_WRITE:
  case STGM_READWRITE:
    break;
  default:
    return E_FAIL;
  }

  switch (share)
  {
  case STGM_SHARE_DENY_NONE:
  case STGM_SHARE_DENY_READ:
  case STGM_SHARE_DENY_WRITE:
  case STGM_SHARE_EXCLUSIVE:
    break;
  case 0:
    if (!(stgm & STGM_TRANSACTED))
      return E_FAIL;
    break;
  default:
    return E_FAIL;
  }

  switch (create)
  {
  case STGM_CREATE:
  case STGM_FAILIFTHERE:
    break;
  default:
    return E_FAIL;
  }

  /*
   * STGM_DIRECT | STGM_TRANSACTED | STGM_SIMPLE
   */
  if ( (stgm & STGM_TRANSACTED) && (stgm & STGM_SIMPLE) )
      return E_FAIL;

  /*
   * STGM_CREATE | STGM_CONVERT
   * if both are false, STGM_FAILIFTHERE is set to TRUE
   */
  if ( create == STGM_CREATE && (stgm & STGM_CONVERT) )
    return E_FAIL;

  /*
   * STGM_NOSCRATCH requires STGM_TRANSACTED
   */
  if ( (stgm & STGM_NOSCRATCH) && !(stgm & STGM_TRANSACTED) )
    return E_FAIL;

  /*
   * STGM_NOSNAPSHOT requires STGM_TRANSACTED and
   * not STGM_SHARE_EXCLUSIVE or STGM_SHARE_DENY_WRITE`
   */
  if ( (stgm & STGM_NOSNAPSHOT) &&
        (!(stgm & STGM_TRANSACTED) ||
         share == STGM_SHARE_EXCLUSIVE ||
         share == STGM_SHARE_DENY_WRITE) )
    return E_FAIL;

  return S_OK;
}