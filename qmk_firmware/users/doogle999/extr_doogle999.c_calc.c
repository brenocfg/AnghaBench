#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char c; scalar_t__ priority; int ltr; } ;
struct TYPE_4__ {double num; TYPE_1__ op; } ;
struct Token {int isNum; TYPE_2__ raw; } ;

/* Variables and functions */
 int CALC_BUFFER_SIZE ; 
#define  CALC_CHAR_ACS 145 
#define  CALC_CHAR_ADD 144 
#define  CALC_CHAR_ASN 143 
#define  CALC_CHAR_ATN 142 
#define  CALC_CHAR_BEG 141 
#define  CALC_CHAR_COS 140 
 char const CALC_CHAR_DEC ; 
#define  CALC_CHAR_DIV 139 
#define  CALC_CHAR_END 138 
#define  CALC_CHAR_EUL 137 
#define  CALC_CHAR_EXP 136 
#define  CALC_CHAR_LGE 135 
#define  CALC_CHAR_LOG 134 
#define  CALC_CHAR_MUL 133 
#define  CALC_CHAR_PI 132 
#define  CALC_CHAR_SIN 131 
#define  CALC_CHAR_SQT 130 
#define  CALC_CHAR_SUB 129 
#define  CALC_CHAR_TAN 128 
 scalar_t__ CALC_PRIO_ADD ; 
 scalar_t__ CALC_PRIO_DIV ; 
 scalar_t__ CALC_PRIO_EXP ; 
 scalar_t__ CALC_PRIO_MUL ; 
 scalar_t__ CALC_PRIO_SUB ; 
 double CALC_VALU_EUL ; 
 double CALC_VALU_PI ; 
 double acos (double) ; 
 double asin (double) ; 
 double atan (double) ; 
 double atof (char*) ; 
 double cos (double) ; 
 double log (double) ; 
 double log10 (double) ; 
 double pow (double,double) ; 
 double sin (double) ; 
 double sqrt (double) ; 
 double tan (double) ; 

__attribute__((used)) static double calc(const char input[CALC_BUFFER_SIZE +1]) // Finds value of input char array, relatively small and fast I think
{
  char inputToken[CALC_BUFFER_SIZE + 1]; // Input buffer, used when a single token (generally a number) takes up more
  unsigned char inputTokenLocation = 0, inputLocation = 0; // Keep track of indices

  struct Token tokens[CALC_BUFFER_SIZE + 1]; // Input, converted to tokens, one extra large to accomodate for possible negative sign then open parenthesis as first character
  unsigned char tokenCount = 0; // Keep track of index

  bool dashAsMinus = false; // Kind of a hacky solution to determining whether to treat a dash as a minus sign or a negative sign

  while(inputLocation < CALC_BUFFER_SIZE + 1)
  {
    char digit = input[inputLocation];

    if(inputLocation == 0 && input[inputLocation] == CALC_CHAR_SUB && input[inputLocation + 1] == CALC_CHAR_BEG)
    {
      tokens[tokenCount].raw.num = 0;
      tokens[tokenCount].isNum = true;

      tokenCount++;
      dashAsMinus = true;
    }

    if ((digit >= '0' && digit <= '9') || /* valid digit */
        (inputTokenLocation != 0 && input[inputLocation] == CALC_CHAR_DEC) || /* valid floating point */
        (!dashAsMinus && inputTokenLocation == 0 && input[inputLocation] == CALC_CHAR_SUB)) /* - is negative sign */
    {
      inputToken[inputTokenLocation] = input[inputLocation];
      inputTokenLocation++;
      inputLocation++;
      continue;
    }

    if(inputTokenLocation != 0)
    {
      // sscanf(inputToken, "%lf", &tokens[tokenCount].raw.num); // I would like to use sscanf here, but the small version of stdio.h on the chip doesn't allow sscanf or its sister functions to be used to process floats
      tokens[tokenCount].raw.num = atof(inputToken);
      tokens[tokenCount].isNum = true;
      for(unsigned char i = 0; i < inputTokenLocation + 1; i++)
      {
        inputToken[i] = '\0';
      }
      inputTokenLocation = 0;
      tokenCount++;
      dashAsMinus = true;
      continue;
    }

    /* inputTokenLocation == 0 */
    tokens[tokenCount].isNum = false;
    tokens[tokenCount].raw.op.c = input[inputLocation];
    tokens[tokenCount].raw.op.priority = 0;
    tokens[tokenCount].raw.op.ltr = true;
    dashAsMinus = false;

    switch(input[inputLocation])
    {
      case CALC_CHAR_BEG:
        break;
      case CALC_CHAR_END:
        dashAsMinus = true;
        break;
      case CALC_CHAR_ADD:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_ADD;
        break;
      case CALC_CHAR_SUB:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_SUB;
        break;
      case CALC_CHAR_MUL:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_MUL;
        break;
      case CALC_CHAR_DIV:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_DIV;
        break;
      case CALC_CHAR_EXP:
        tokens[tokenCount].raw.op.priority = CALC_PRIO_EXP;
        tokens[tokenCount].raw.op.ltr = false;
        break;
      case CALC_CHAR_SIN:
      case CALC_CHAR_COS:
      case CALC_CHAR_TAN:
      case CALC_CHAR_ASN:
      case CALC_CHAR_ACS:
      case CALC_CHAR_ATN:
      case CALC_CHAR_LGE:
      case CALC_CHAR_LOG:
      case CALC_CHAR_SQT:
        break;
      case CALC_CHAR_EUL:
        tokens[tokenCount].isNum = true;
        tokens[tokenCount].raw.num = CALC_VALU_EUL;
        dashAsMinus = true;
        break;
      case CALC_CHAR_PI:
        tokens[tokenCount].isNum = true;
        tokens[tokenCount].raw.num = CALC_VALU_PI;
        dashAsMinus = true;
        break;
      case '\0':
        tokenCount--;
        inputLocation = CALC_BUFFER_SIZE;
        break;
      default:
        tokenCount--;
        break;
    }
    tokenCount++;
    inputLocation++;
  }

  struct Token output[CALC_BUFFER_SIZE + 1]; // Final output tokens before evaluation
  struct Token opstack[CALC_BUFFER_SIZE + 1]; // Stack of operators
  unsigned char outputLocation = 0, opstackLocation = 0; // Keep track of indices

  unsigned char numBrackets = 0; // The number of parenthesis

  for(unsigned char i = 0; i < tokenCount; i++)
  {
    if(tokens[i].isNum)
    {
      output[outputLocation] = tokens[i];
      outputLocation++;
    }
    else if(tokens[i].raw.op.c == CALC_CHAR_BEG)
    {
      opstack[opstackLocation] = tokens[i];
      opstackLocation++;
    }
    else if(tokens[i].raw.op.c == CALC_CHAR_END)
    {
      while(opstack[opstackLocation - 1].raw.op.c != CALC_CHAR_BEG)
      {
        output[outputLocation] = opstack[opstackLocation - 1];
        outputLocation++;
        opstackLocation--;
      }
      opstackLocation--;

      numBrackets += 2;
    }
    else if(tokens[i].raw.op.priority == 0)
    {
      opstack[opstackLocation] = tokens[i];
      opstackLocation++;
    }
    else
    {
      while(opstackLocation != 0
        && (opstack[opstackLocation - 1].raw.op.priority == 0
          || tokens[i].raw.op.priority < opstack[opstackLocation - 1].raw.op.priority
          || (tokens[i].raw.op.priority == opstack[opstackLocation - 1].raw.op.priority && opstack[opstackLocation - 1].raw.op.ltr))
        && opstack[opstackLocation - 1].raw.op.c != CALC_CHAR_BEG)
      {
        output[outputLocation] = opstack[opstackLocation - 1];
        outputLocation++;
        opstackLocation--;
      }
      opstack[opstackLocation] = tokens[i];
      opstackLocation++;
    }
  }

  tokenCount -= numBrackets;

  for(signed char i = opstackLocation - 1; i >= 0; i--)
  {
    output[outputLocation] = opstack[i];
    outputLocation++;
    opstackLocation--;
  }

  double answer[CALC_BUFFER_SIZE];
  unsigned char answerLocation = 0;

  for(unsigned char i = 0; i < tokenCount; i++)
  {
    if(output[i].isNum)
    {
      answer[answerLocation] = output[i].raw.num;
      answerLocation++;
      continue;
    }

    if(output[i].raw.op.priority == 0)
    {
      if (answerLocation < 1) { /* not handled here -- ERROR? */ } else
      if(answerLocation >= 1)
      {
        double (*op)(double);
        switch(output[i].raw.op.c)
        {
        case CALC_CHAR_SIN:
          op = sin;
          break;
        case CALC_CHAR_COS:
          op = cos;
          break;
        case CALC_CHAR_TAN:
          op = tan;
          break;
        case CALC_CHAR_ASN:
          op = asin;
          break;
        case CALC_CHAR_ACS:
          op = acos;
          break;
        case CALC_CHAR_ATN:
          op = atan;
          break;
        case CALC_CHAR_LGE:
          op = log;
          break;
        case CALC_CHAR_LOG:
          op = log10;
          break;
        case CALC_CHAR_SQT:
          op = sqrt;
          break;
        default:
          continue; /* invalid input */
        }
        answer[answerLocation - 1] = op(answer[answerLocation - 1]);
      }
    }
    /* priority != 0 */
    else if(answerLocation >= 2)
    {
      switch(output[i].raw.op.c)
      {
      case CALC_CHAR_ADD:
        answer[answerLocation - 2] += answer[answerLocation - 1];
        break;
      case CALC_CHAR_SUB:
        answer[answerLocation - 2] -= answer[answerLocation - 1];
        break;
      case CALC_CHAR_MUL:
        answer[answerLocation - 2] *= answer[answerLocation - 1];
        break;
      case CALC_CHAR_DIV:
        answer[answerLocation - 2] /= answer[answerLocation - 1];
        break;
      case CALC_CHAR_EXP:
        answer[answerLocation - 2] = pow(answer[answerLocation - 2], answer[answerLocation - 1]);
        break;
      }

      answerLocation--;
    }
  }

  return answer[0];
}