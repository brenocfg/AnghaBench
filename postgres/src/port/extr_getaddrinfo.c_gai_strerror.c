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
#define  EAI_AGAIN 136 
#define  EAI_BADFLAGS 135 
#define  EAI_FAIL 134 
#define  EAI_FAMILY 133 
#define  EAI_MEMORY 132 
#define  EAI_NODATA 131 
#define  EAI_NONAME 130 
#define  EAI_SERVICE 129 
#define  EAI_SOCKTYPE 128 
 int HOST_NOT_FOUND ; 
 int NO_RECOVERY ; 
 int TRY_AGAIN ; 
 char const* hstrerror (int) ; 

const char *
gai_strerror(int errcode)
{
#ifdef HAVE_HSTRERROR
	int			hcode;

	switch (errcode)
	{
		case EAI_NONAME:
			hcode = HOST_NOT_FOUND;
			break;
		case EAI_AGAIN:
			hcode = TRY_AGAIN;
			break;
		case EAI_FAIL:
		default:
			hcode = NO_RECOVERY;
			break;
	}

	return hstrerror(hcode);
#else							/* !HAVE_HSTRERROR */

	switch (errcode)
	{
		case EAI_NONAME:
			return "Unknown host";
		case EAI_AGAIN:
			return "Host name lookup failure";
			/* Errors below are probably WIN32 only */
#ifdef EAI_BADFLAGS
		case EAI_BADFLAGS:
			return "Invalid argument";
#endif
#ifdef EAI_FAMILY
		case EAI_FAMILY:
			return "Address family not supported";
#endif
#ifdef EAI_MEMORY
		case EAI_MEMORY:
			return "Not enough memory";
#endif
#if defined(EAI_NODATA) && EAI_NODATA != EAI_NONAME /* MSVC/WIN64 duplicate */
		case EAI_NODATA:
			return "No host data of that type was found";
#endif
#ifdef EAI_SERVICE
		case EAI_SERVICE:
			return "Class type not found";
#endif
#ifdef EAI_SOCKTYPE
		case EAI_SOCKTYPE:
			return "Socket type not supported";
#endif
		default:
			return "Unknown server error";
	}
#endif							/* HAVE_HSTRERROR */
}