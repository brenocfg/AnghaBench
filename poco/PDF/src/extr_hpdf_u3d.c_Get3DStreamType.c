#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  error; } ;
typedef  int HPDF_UINT ;
typedef  TYPE_1__* HPDF_Stream ;
typedef  scalar_t__ HPDF_STATUS ;
typedef  int /*<<< orphan*/  HPDF_BYTE ;

/* Variables and functions */
 scalar_t__ HPDF_Error_GetCode (int /*<<< orphan*/ ) ; 
 scalar_t__ HPDF_INVALID_U3D_DATA ; 
 scalar_t__ HPDF_MemCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ HPDF_OK ; 
 int /*<<< orphan*/  HPDF_PTRACE (char*) ; 
 int /*<<< orphan*/  HPDF_SEEK_SET ; 
 scalar_t__ HPDF_Stream_Read (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ HPDF_Stream_Seek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* prc ; 
 char* u3d ; 

__attribute__((used)) static HPDF_STATUS Get3DStreamType (HPDF_Stream  stream, const char **type)
{
	HPDF_BYTE tag[4];
	HPDF_UINT len;

	HPDF_PTRACE ((" HPDF_U3D_Get3DStreamType\n"));

	len = 4;
	if (HPDF_Stream_Read (stream, tag, &len) != HPDF_OK) {
		return HPDF_Error_GetCode (stream->error);
	}

	if (HPDF_Stream_Seek (stream, 0, HPDF_SEEK_SET) != HPDF_OK) {
		return HPDF_Error_GetCode (stream->error);
	}

	if (HPDF_MemCmp(tag, (HPDF_BYTE *)u3d, 4/* yes, \0 is required */) == 0) {
		*type = u3d;
		return HPDF_OK;
	}

	if (HPDF_MemCmp(tag, (HPDF_BYTE *)prc, 3) == 0) {
		*type = prc;
		return HPDF_OK;
	}

	return HPDF_INVALID_U3D_DATA;
}