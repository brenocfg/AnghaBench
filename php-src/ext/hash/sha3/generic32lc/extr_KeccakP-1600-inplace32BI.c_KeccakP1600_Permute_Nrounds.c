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
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  Abe0 ; 
 int /*<<< orphan*/  Abi0 ; 
 int /*<<< orphan*/  Abo0 ; 
 int /*<<< orphan*/  Abu0 ; 
 int /*<<< orphan*/  Aga0 ; 
 int /*<<< orphan*/  Age0 ; 
 int /*<<< orphan*/  Agi0 ; 
 int /*<<< orphan*/  Ago0 ; 
 int /*<<< orphan*/  Aka0 ; 
 int /*<<< orphan*/  Ake0 ; 
 int /*<<< orphan*/  Aki0 ; 
 int /*<<< orphan*/  Ako0 ; 
 int /*<<< orphan*/  Ako1 ; 
 int /*<<< orphan*/  Aku0 ; 
 int /*<<< orphan*/  Ama0 ; 
 int /*<<< orphan*/  Ame0 ; 
 int /*<<< orphan*/  Ami0 ; 
 int /*<<< orphan*/  Ami1 ; 
 int /*<<< orphan*/  Amo0 ; 
 int /*<<< orphan*/  Amu0 ; 
 int /*<<< orphan*/  Asa0 ; 
 int /*<<< orphan*/  Asi0 ; 
 int /*<<< orphan*/  Aso0 ; 
 int /*<<< orphan*/  Asu0 ; 
 int* KeccakF1600RoundConstants_int2 ; 
 int /*<<< orphan*/  KeccakRound0 () ; 
 int /*<<< orphan*/  KeccakRound1 () ; 
 int /*<<< orphan*/  KeccakRound2 () ; 
 int /*<<< orphan*/  KeccakRound3 () ; 
 int /*<<< orphan*/  SwapEO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SwapPI13 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  SwapPI2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void KeccakP1600_Permute_Nrounds(void *state, unsigned int nRounds)
{
    UINT32 Da0, De0, Di0, Do0, Du0;
    UINT32 Da1, De1, Di1, Do1, Du1;
    UINT32 Ba, Be, Bi, Bo, Bu;
    UINT32 Cx, Cy, Cz, Cw;
    const UINT32 *pRoundConstants = KeccakF1600RoundConstants_int2+(24-nRounds)*2;
    UINT32 *stateAsHalfLanes = (UINT32*)state;
    #define Aba0 stateAsHalfLanes[ 0]
    #define Aba1 stateAsHalfLanes[ 1]
    #define Abe0 stateAsHalfLanes[ 2]
    #define Abe1 stateAsHalfLanes[ 3]
    #define Abi0 stateAsHalfLanes[ 4]
    #define Abi1 stateAsHalfLanes[ 5]
    #define Abo0 stateAsHalfLanes[ 6]
    #define Abo1 stateAsHalfLanes[ 7]
    #define Abu0 stateAsHalfLanes[ 8]
    #define Abu1 stateAsHalfLanes[ 9]
    #define Aga0 stateAsHalfLanes[10]
    #define Aga1 stateAsHalfLanes[11]
    #define Age0 stateAsHalfLanes[12]
    #define Age1 stateAsHalfLanes[13]
    #define Agi0 stateAsHalfLanes[14]
    #define Agi1 stateAsHalfLanes[15]
    #define Ago0 stateAsHalfLanes[16]
    #define Ago1 stateAsHalfLanes[17]
    #define Agu0 stateAsHalfLanes[18]
    #define Agu1 stateAsHalfLanes[19]
    #define Aka0 stateAsHalfLanes[20]
    #define Aka1 stateAsHalfLanes[21]
    #define Ake0 stateAsHalfLanes[22]
    #define Ake1 stateAsHalfLanes[23]
    #define Aki0 stateAsHalfLanes[24]
    #define Aki1 stateAsHalfLanes[25]
    #define Ako0 stateAsHalfLanes[26]
    #define Ako1 stateAsHalfLanes[27]
    #define Aku0 stateAsHalfLanes[28]
    #define Aku1 stateAsHalfLanes[29]
    #define Ama0 stateAsHalfLanes[30]
    #define Ama1 stateAsHalfLanes[31]
    #define Ame0 stateAsHalfLanes[32]
    #define Ame1 stateAsHalfLanes[33]
    #define Ami0 stateAsHalfLanes[34]
    #define Ami1 stateAsHalfLanes[35]
    #define Amo0 stateAsHalfLanes[36]
    #define Amo1 stateAsHalfLanes[37]
    #define Amu0 stateAsHalfLanes[38]
    #define Amu1 stateAsHalfLanes[39]
    #define Asa0 stateAsHalfLanes[40]
    #define Asa1 stateAsHalfLanes[41]
    #define Ase0 stateAsHalfLanes[42]
    #define Ase1 stateAsHalfLanes[43]
    #define Asi0 stateAsHalfLanes[44]
    #define Asi1 stateAsHalfLanes[45]
    #define Aso0 stateAsHalfLanes[46]
    #define Aso1 stateAsHalfLanes[47]
    #define Asu0 stateAsHalfLanes[48]
    #define Asu1 stateAsHalfLanes[49]

    nRounds &= 3;
    switch ( nRounds )
    {
        #define I0 Ba
        #define I1 Be
        #define T0 Bi
        #define T1 Bo
        #define SwapPI13( in0,in1,in2,in3,eo0,eo1,eo2,eo3 ) \
            I0 = (in0)[0]; I1 = (in0)[1];       \
            T0 = (in1)[0]; T1 = (in1)[1];       \
            (in0)[eo0] = T0; (in0)[eo0^1] = T1; \
            T0 = (in2)[0]; T1 = (in2)[1];       \
            (in1)[eo1] = T0; (in1)[eo1^1] = T1; \
            T0 = (in3)[0]; T1 = (in3)[1];       \
            (in2)[eo2] = T0; (in2)[eo2^1] = T1; \
            (in3)[eo3] = I0; (in3)[eo3^1] = I1
        #define SwapPI2( in0,in1,in2,in3 ) \
            I0 = (in0)[0]; I1 = (in0)[1]; \
            T0 = (in1)[0]; T1 = (in1)[1]; \
            (in0)[1] = T0; (in0)[0] = T1; \
            (in1)[1] = I0; (in1)[0] = I1; \
            I0 = (in2)[0]; I1 = (in2)[1]; \
            T0 = (in3)[0]; T1 = (in3)[1]; \
            (in2)[1] = T0; (in2)[0] = T1; \
            (in3)[1] = I0; (in3)[0] = I1
        #define SwapEO( even,odd ) T0 = even; even = odd; odd = T0

        case 1:
            SwapPI13( &Aga0, &Aka0, &Asa0, &Ama0, 1, 0, 1, 0 );
            SwapPI13( &Abe0, &Age0, &Ame0, &Ake0, 0, 1, 0, 1 );
            SwapPI13( &Abi0, &Aki0, &Agi0, &Asi0, 1, 0, 1, 0 );
            SwapEO( Ami0, Ami1 );
            SwapPI13( &Abo0, &Amo0, &Aso0, &Ago0, 1, 0, 1, 0 );
            SwapEO( Ako0, Ako1 );
            SwapPI13( &Abu0, &Asu0, &Aku0, &Amu0, 0, 1, 0, 1 );
            break;

        case 2:
            SwapPI2( &Aga0, &Asa0, &Aka0, &Ama0 );
            SwapPI2( &Abe0, &Ame0, &Age0, &Ake0 );
            SwapPI2( &Abi0, &Agi0, &Aki0, &Asi0 );
            SwapPI2( &Abo0, &Aso0, &Ago0, &Amo0 );
            SwapPI2( &Abu0, &Aku0, &Amu0, &Asu0 );
            break;

        case 3:
            SwapPI13( &Aga0, &Ama0, &Asa0, &Aka0, 0, 1, 0, 1 );
            SwapPI13( &Abe0, &Ake0, &Ame0, &Age0, 1, 0, 1, 0 );
            SwapPI13( &Abi0, &Asi0, &Agi0, &Aki0, 0, 1, 0, 1 );
            SwapEO( Ami0, Ami1 );
            SwapPI13( &Abo0, &Ago0, &Aso0, &Amo0, 0, 1, 0, 1 );
            SwapEO( Ako0, Ako1 );
            SwapPI13( &Abu0, &Amu0, &Aku0, &Asu0, 1, 0, 1, 0 );
            break;
        #undef I0
        #undef I1
        #undef T0
        #undef T1
        #undef SwapPI13
        #undef SwapPI2
        #undef SwapEO
    }

    do
    {
        /* Code for 4 rounds, using factor 2 interleaving, 64-bit lanes mapped to 32-bit words */
        switch ( nRounds )
        {
            case 0: KeccakRound0(); /* fall through */
            case 3: KeccakRound1();
            case 2: KeccakRound2();
            case 1: KeccakRound3();
        }
        nRounds = 0;
    }
    while ( *pRoundConstants != 0xFF );

    #undef Aba0
    #undef Aba1
    #undef Abe0
    #undef Abe1
    #undef Abi0
    #undef Abi1
    #undef Abo0
    #undef Abo1
    #undef Abu0
    #undef Abu1
    #undef Aga0
    #undef Aga1
    #undef Age0
    #undef Age1
    #undef Agi0
    #undef Agi1
    #undef Ago0
    #undef Ago1
    #undef Agu0
    #undef Agu1
    #undef Aka0
    #undef Aka1
    #undef Ake0
    #undef Ake1
    #undef Aki0
    #undef Aki1
    #undef Ako0
    #undef Ako1
    #undef Aku0
    #undef Aku1
    #undef Ama0
    #undef Ama1
    #undef Ame0
    #undef Ame1
    #undef Ami0
    #undef Ami1
    #undef Amo0
    #undef Amo1
    #undef Amu0
    #undef Amu1
    #undef Asa0
    #undef Asa1
    #undef Ase0
    #undef Ase1
    #undef Asi0
    #undef Asi1
    #undef Aso0
    #undef Aso1
    #undef Asu0
    #undef Asu1
}