#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {char const* member_0; int /*<<< orphan*/ * uri; TYPE_7__** playInterface; TYPE_8__** player; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ uri_player ;
struct TYPE_26__ {scalar_t__ (* Realize ) (TYPE_8__**,int /*<<< orphan*/ ) ;scalar_t__ (* GetInterface ) (TYPE_8__**,int /*<<< orphan*/ ,TYPE_7__***) ;} ;
struct TYPE_25__ {scalar_t__ (* SetPlayState ) (TYPE_7__**,int /*<<< orphan*/ ) ;} ;
struct TYPE_24__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_23__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_22__ {int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_21__ {int /*<<< orphan*/ * member_1; TYPE_5__* member_0; } ;
struct TYPE_20__ {TYPE_6__* member_1; TYPE_4__* member_0; } ;
struct TYPE_18__ {scalar_t__ (* CreateAudioPlayer ) (TYPE_11__**,TYPE_8__***,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ SLresult ;
typedef  int /*<<< orphan*/  SLchar ;
typedef  TYPE_2__ SLDataSource ;
typedef  TYPE_3__ SLDataSink ;
typedef  TYPE_4__ SLDataLocator_URI ;
typedef  TYPE_5__ SLDataLocator_OutputMix ;
typedef  TYPE_6__ SLDataFormat_MIME ;

/* Variables and functions */
 int /*<<< orphan*/  SL_BOOLEAN_FALSE ; 
 int /*<<< orphan*/  SL_CONTAINERTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  SL_DATAFORMAT_MIME ; 
 int /*<<< orphan*/  SL_DATALOCATOR_OUTPUTMIX ; 
 int /*<<< orphan*/  SL_DATALOCATOR_URI ; 
 int /*<<< orphan*/  SL_IID_PLAY ; 
 int /*<<< orphan*/  SL_PLAYSTATE_PAUSED ; 
 scalar_t__ SL_RESULT_SUCCESS ; 
 TYPE_11__** engineInterface ; 
 int /*<<< orphan*/  outputMix ; 
 TYPE_1__* players ; 
 scalar_t__ stub1 (TYPE_11__**,TYPE_8__***,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_8__**,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (TYPE_8__**,int /*<<< orphan*/ ,TYPE_7__***) ; 
 scalar_t__ stub4 (TYPE_7__**,int /*<<< orphan*/ ) ; 

uri_player* slplay_create_player_for_uri(const char* uri, char **error) {
  uri_player player = { uri, NULL, NULL };

  SLresult result;
  SLDataLocator_URI locUri = {SL_DATALOCATOR_URI, (SLchar *) uri};
  SLDataFormat_MIME formatMime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
  SLDataSource audioSrc = {&locUri, &formatMime};

  SLDataLocator_OutputMix outMix = {SL_DATALOCATOR_OUTPUTMIX, outputMix};
  SLDataSink audioSnk = {&outMix, NULL};

  result = (*engineInterface)->CreateAudioPlayer(engineInterface, &player.player, &audioSrc, &audioSnk, 0, NULL, NULL);
  if (result != SL_RESULT_SUCCESS) {
    *error = "Failed to create audio player";
    return NULL;
  }

  result = (*(player.player))->Realize(player.player, SL_BOOLEAN_FALSE);
  if (result != SL_RESULT_SUCCESS) {
    *error = "Failed to realize audio player";
    return NULL;
  }

  result = (*(player.player))->GetInterface(player.player, SL_IID_PLAY, &(player.playInterface));
  if (result != SL_RESULT_SUCCESS) {
    *error = "Failed to get player interface";
    return NULL;
  }

  result = (*(player.playInterface))->SetPlayState(player.playInterface, SL_PLAYSTATE_PAUSED);
  if (result != SL_RESULT_SUCCESS) {
    *error = "Failed to initialize playstate to SL_PLAYSTATE_PAUSED";
    return NULL;
  }

  uri_player *p = players;
  while (p->uri != NULL) {
    p++;
  }
  *p = player;

  return p;
}