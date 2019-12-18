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
struct TYPE_3__ {int overwrite; int streamChecksum; int blockIndependence; int sparseFileSupport; scalar_t__ removeSrcFile; int /*<<< orphan*/ * dictionaryFilename; scalar_t__ favorDecSpeed; scalar_t__ useDictionary; scalar_t__ contentSizeFlag; scalar_t__ blockChecksum; scalar_t__ blockSize; int /*<<< orphan*/  blockSizeId; scalar_t__ testMode; scalar_t__ passThrough; } ;
typedef  TYPE_1__ LZ4IO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 int /*<<< orphan*/  LZ4IO_BLOCKSIZEID_DEFAULT ; 
 scalar_t__ malloc (int) ; 

LZ4IO_prefs_t* LZ4IO_defaultPreferences(void)
{
  LZ4IO_prefs_t* const ret = (LZ4IO_prefs_t*)malloc(sizeof(LZ4IO_prefs_t));
  if (!ret) EXM_THROW(21, "Allocation error : not enough memory");
  ret->passThrough = 0;
  ret->overwrite = 1;
  ret->testMode = 0;
  ret->blockSizeId = LZ4IO_BLOCKSIZEID_DEFAULT;
  ret->blockSize = 0;
  ret->blockChecksum = 0;
  ret->streamChecksum = 1;
  ret->blockIndependence = 1;
  ret->sparseFileSupport = 1;
  ret->contentSizeFlag = 0;
  ret->useDictionary = 0;
  ret->favorDecSpeed = 0;
  ret->dictionaryFilename = NULL;
  ret->removeSrcFile = 0;
  return ret;
}